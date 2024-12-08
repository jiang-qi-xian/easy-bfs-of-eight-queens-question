#include<iostream>
#include<stack>
#include<queue>
#include<string>
#include<vector>
#include<map>
using namespace std;
map<string, int>visited;
map<string, string>link;//父子关系
int ok(string state) {
  int num = 0;/*计算逆序对数*/
  for (int i = 1; i < state.size(); ++i) {
    if (state[i] != '0') {
      for (int j = 0; j < i; ++j) {
        if (state.at(i) < state.at(j) && state[j != '0']) {
          ++num;
        }
      }
    }
  }
  return num ;/*判断奇偶性*/
}
void printmatrix(string state) {
  for (int i = 0; i < 9; ++i) {
    cout << state[i] << ' ';
    if ((i + 1) % 3 == 0) {
      cout << endl;
    }
  }
  cout << "-----------------------------------" << endl;
}
void bfs(string state,string target) {
  int move[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };//上下左右四个移动方向
  queue<string> bfsqueue;//存放搜索状态
  bfsqueue.push(state);
  visited[state] = 1;//已访问
  while (!bfsqueue.empty()) {//如果不为空，说明可以继续
    string str = bfsqueue.front();//把状态取出来
    int x, y, index, nx, ny,nindex;
    if (str == target) {//如果移动到了目标，结束
      return;
    }
    index = str.find('0');//确定空格的位置
    x = index % 3;//空格横坐标
    y = index / 3;//纵坐标
    for (int i = 0; i < 4; ++i) {//四个方向遍历
      str = bfsqueue.front();
      nx = x + move[i][0];
      ny = y + move[i][1];
      if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {//限定范围
        nindex = nx + ny * 3;
        str[index] = str[nindex];//改变状态，输入的是一串字符，所以在那一串上面直接改
        str[nindex] = '0';
        if (visited.find(str) == visited.end()) {
          // 保存当前状态的父状态，用于后续回溯路径
          link[str] = bfsqueue.front();
          bfsqueue.push(str);//入栈
          visited[str] = 1;//标记该状态已访问
        }
      }
    }
    bfsqueue.pop();//一个状态的四个方向产生了，把这个遍历过的状态出栈
  }
}
void printbfs(string state,string target) {
  stack<string> stack;
  string str = target;
  while (str != state) {
    stack.push(str);
    str = link[str];
  }
  stack.push(state);
  int num = stack.size();
  while (!stack.empty()) {
    printmatrix(stack.top());
    stack.pop();
  }
  cout << "一共有" << num - 1 << "步" << endl; //逆序打印会把初始状态也算进num，所以-1
}
int main() {
  string str,target;
  int okstate, oktarget;
  cout << "请输入初始状态：（0代表空格）" << endl;
  cin >> str;
  cout << "请输入最终状态：（0代表空格）" << endl;
  cin >> target;
  okstate = ok(str) % 2;
  oktarget = ok(target) % 2;
  if (okstate == oktarget) {
    bfs(str, target);
    printbfs(str, target);
  }
  else {
    cout << "无法完成" << endl;
  }
  return 0;
}
