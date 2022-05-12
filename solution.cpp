#include "solution.h"
#include "util.h"
#include <unordered_set>
#include <numeric>
#include <iterator>
#include <unordered_map>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>
#include <stack>
using namespace sol2249;
using namespace std;

/*takeaways
  - use brute force and pre-calculate the cumulative sum of each
    row and column to make later calculation easier
  - it's very easy to get it wrong in determining the range of
    indexes
    - possible top-left corner indexes (x,y)
      - assume the matrix is 4x3 (mxn) , so the biggest square is 3x3 (kxk)
      - so for the first row, the allowed corner are (0,0) and (0,1)
        - from the very last qualified ith element to the very end we
          should have k elements
          (m-1) - i + 1 = k  =>  m = i + k
        - any smaller i would work so i+k <= m

*/

int Solution::findLargest(vector<vector<int>> &grid)
{
  const int m = grid.size();
  const int n = grid[0].size();

  /* cumulative sum
     - if grid[0][0..3] = {5,1,3,1}, rSum[0][0..4] = {0,5,6,9,10}
     - so rSum[0][j] records the total sum of the numbers
       from grid[0][0] to grid[0][j-1] or whatever comes
       before grid[0][j]
     - so if we want to find the sum from grid[0][1] with the
       size of square k being 2, it will be:
       rSum[0][1+k] - rSum[0][1] = rSum[0][3] - rSum[0][1]
                                 = 9 - 5 = 4
       - you can think of this as
         whatever before grid[0][1+k] => grid[0][0] + grid[0][1] + grid[0][2]
         subtract whatever before gird[0][1] => grid[0][0]
         will give you grid[0][1] + grid[0][2]

  */

  auto rSum = vector<vector<int>>(m, vector<int>(n + 1));
  auto cSum = vector<vector<int>>(n, vector<int>(m + 1));

  for (auto i = 0; i < m; i++)
    for (auto j = 0; j < n; j++)
    {
      rSum[i][j + 1] = grid[i][j] + rSum[i][j];
      /* cSum[j][i] is the sum of grid[0..i-1][j]
         - don't get confused
      */
      cSum[j][i + 1] = grid[i][j] + cSum[j][i];
    }

  /* from big to small so we can find the largest square */
  for (int k = min(m, n); k >= 2; k--)
    /* the last element and i should have at least k numbers
       (m-1) - i + 1 >=K, so m >= i + k
       - (i,j) is the top-left corner of the square
    */
    for (auto i = 0; i + k <= m; i++)
      for (auto j = 0; j + k <= n; j++)
      {
        /* examine the square with top-left corner starts at (x,y) */
        auto s = vector<int>();
        /* calculate the sum of each row */
        for (auto r = 0; r < k; r++)
          /* same row
             - whatever before grid[i+r][j+k]
               subtract whatever before grid[i+r][j]
               should give you the sum of
               grid[i+r][j] + ... + grid[i+r][j+k-1]
          */
          s.push_back(rSum[i + r][j + k] - rSum[i + r][j]);
        /* calculate the sum of each col */
        for (auto c = 0; c < k; c++)
          s.push_back(cSum[j + c][i + k] - cSum[j + c][i]);

        /* diagonal, anti-diagonal */
        auto d = 0, ad = 0;

        for (auto l = 0; l < k; l++)
        {
          d += grid[i + l][j + l];
          /* the index of  the very last element
             in the first row is j + k - 1 */
          ad += grid[i + l][j + k - 1 - l];
        }
        s.push_back(d);
        s.push_back(ad);

        if (count(begin(s), end(s), s[0]) == s.size())
          return k;
      }

  return 1;
}