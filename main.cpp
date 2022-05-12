#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol2249;

/*
Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
Output: 3
*/

tuple<vector<vector<int>>, int>
testFixture1()
{
  auto grid = vector<vector<int>>{
      {7, 1, 4, 5, 6}, {2, 5, 1, 6, 4}, {1, 5, 4, 3, 2}, {1, 2, 7, 3, 4}};
  return make_tuple(grid, 3);
}

/*
Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]

Output: 2
*/

tuple<vector<vector<int>>, int>
testFixture2()
{
  auto grid = vector<vector<int>>{
      {5, 1, 3, 1}, {9, 3, 3, 1}, {1, 3, 3, 8}};
  return make_tuple(grid, 2);
}

void test1()
{
  auto f = testFixture1();
  cout << "Expect to see: " << get<1>(f) << endl;
  Solution sol;
  cout << sol.findLargest(get<0>(f)) << endl;
}

void test2()
{
  auto f = testFixture2();
  cout << "Expect to see: " << get<1>(f) << endl;
  Solution sol;
  cout << sol.findLargest(get<0>(f)) << endl;
}

main()
{
  test1();
  test2();
  return 0;
}