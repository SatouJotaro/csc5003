#include<iostream>
#include<string>
#include<algorithm>
#include<cctype>

using namespace std;

// 将字符串转换为小写，方便统一比较
void toLower(string &s){
    for(char &c : s){
        c = tolower(c);
    }
}
int main(){
    string word, article;
    // 读取单词（不含空格）
    cin >> word;
    // 吃掉单词后面的换行符
    string dummy;
    getline(cin, dummy);
    // 读取整篇文章（含空格）
    getline(cin, article);

    // 转换为小写
    toLower(word);
    toLower(article);

    int count = 0;
    int first_pos = -1;
    int word_len = word.length();
    int article_len = article.length();

    // 在文章中循环查找单词
    size_t pos = article.find(word, 0);
    while(pos != string::npos){

        // 检查边界条件
        // 1. 左边界条件：pos 是开头 或者 单词前一个字符是空格
        bool left_ok = (pos == 0) || (article[pos - 1] == ' ');
        // 2. 右边界条件：pos+长度 是文章末尾 或者 单词后一个字符是空格
        bool right_ok = (pos + word_len == article_len) || (article[pos + word_len] == ' ');

        if(left_ok && right_ok){
            count++;
            if(first_pos == -1){
                first_pos = (int)pos;
            }
        }

        // 继续往下寻找下一个匹配点
        pos = article.find(word, pos + 1);
    }

    // 输出结果
    if(count == 0){
        cout << -1 << endl;
    } else {
        cout << count << " " << first_pos << endl;
    }
    return 0;
}