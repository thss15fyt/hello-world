#include<iostream>
#include<string>
#include<stack>
using namespace std;
int isOperator(char x);
int isOperand(char x);
int compareTwo(char o1, char o2, int* first);

int main()
{
	//first statement
	cout << "本程序用于实现命题公式到波兰式、逆波兰式的转换" << endl;
	cout << "请用a~z,A~Z表示命题变项" << endl;
	cout << "分别用 ! & | ^ ~ 代表否定、合取、析取、蕴含和双重蕴含" << endl;
	cout << "请输入一个命题公式：";
	//定义优先级
	int first[200];
	first['!'] = 1;
	first['&'] = 2;
	first['|'] = 3;
	first['^'] = 4;
	first['~'] = 5;
	first['#'] = 6;
	//get data
	stack<char> s1, s2; //s1存储操作数，s2存储操作符
	char line[1000];
	char ans[1000];
	gets(line);
	s2.push('#');
	/*计算波兰式*/
	//scan
	int i, flag = 0, num, len = strlen(line);
	i = len - 1;
	while(i >= 0)
	{
		if(!isOperand(line[i])&&!isOperator(line[i]))
		{
			flag = 1;
			break;
		}
	else{
		if(isOperand(line[i]))        //操作数直接放入s1
			s1.push(line[i]);
		else						//若为操作符
		{
			if(line[i] == ')')       //是右括号，直接放入
				s2.push(line[i]);
			else if(line[i] == '(')     //是左括号，将s2中右括号前面的依次弹出放入s1，并抛弃右括号
			{
				while(s2.top() != ')')
				{
					s1.push(s2.top());
					s2.pop();
				}
				s2.pop();
			}
			else                     //是五种运算符
			{
				if(s2.top() == ')')      //s2顶部为右括号，则直接压入s2
					s2.push(line[i]);
				else          
				{
					if(compareTwo(line[i], s2.top(), first) == 1 || compareTwo(line[i], s2.top(), first) == 0
						||(s2.top() == '!'&&line[i] == '!'))
						s2.push(line[i]);                   //若比顶部运算符优先或相同或均为一元运算符
					else
					{
						while(!(compareTwo(line[i], s2.top(), first) == 1 || s2.top() == ')'))
						{
							s1.push(s2.top());
							s2.pop();
						}
						s2.push(line[i]);
					}
				}
			}
		}
	}
		i--;
	}
	while(s2.top() != '#')
	{
		s1.push(s2.top());
		s2.pop();
	}
	if(flag == 1)
	{
		cout << "输入命题公式有误！"<< endl;
		system("pause");
		return 0;
	}
	else
	{
		cout << "波兰式为：  ";
		while(!s1.empty())
		{
			cout << s1.top();
			s1.pop();
		}
		cout << endl;
	}
	/*波兰式计算结束*/
	//还原数据
	i = 0; 
	while(line[i] != '\0')
	{
		if(isOperand(line[i]))        //操作数直接放入s1
			s1.push(line[i]);
		else						//若为操作符
		{
			if(line[i] == '(')       //是左括号，直接放入
				s2.push(line[i]);
			else if(line[i] == ')')     //是右括号，将s2中左括号前面的依次弹出放入s1，并抛弃左括号
			{
				while(s2.top() != '(')
				{
					s1.push(s2.top());
					s2.pop();
				}
				s2.pop();
			}
			else                     //是五种运算符
			{
				if(s2.top() == '(')      //s2顶部为左括号，则直接压入s2
					s2.push(line[i]);
				else          
				{
					if(compareTwo(line[i], s2.top(), first) == 1 ||(s2.top() == '!'&&line[i] == '!'))
						s2.push(line[i]);                   //若比顶部运算符优先或均为一元运算符
					else
					{
						while(!(compareTwo(line[i], s2.top(), first) == 1 || s2.top() == '('))
						{
							s1.push(s2.top());
							s2.pop();
						}
						s2.push(line[i]);
					}
				}
			}
		}
		i++;
	}
	while(s2.top() != '#')
	{
		s1.push(s2.top());
		s2.pop();
	}
	
		cout << "逆波兰式为：";
		i = 0;
		while(!s1.empty())
		{
			ans[i] = s1.top();
			s1.pop();
			i++;
		}
		num = i - 1;
		for(i = num; i >= 0; i--)
			cout << ans[i];
		cout << endl;
	
	system("pause");
	return 0;
}

int isOperator(char x)
{
	if(x == '!' || x == '&' || x == '|' ||
		x == '^' || x == '~' || x == '(' || x == ')')
		return 1;
	else
		return 0;
}
int isOperand(char x)
{
	if((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return 1;
	else
		return 0;
}
int compareTwo(char o1, char o2, int* first)
{
	if(first[o1] == first[o2])
		return 0;
	else if(first[o1] < first[o2])
		return 1;
	else
		return -1;
}