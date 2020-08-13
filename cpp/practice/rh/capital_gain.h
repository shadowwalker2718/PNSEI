#ifndef PNSEI_CAPITAL_GAIN_H
#define PNSEI_CAPITAL_GAIN_H
/* https://www.1point3acres.com/bbs/thread-642403-1-1.html
2020(4-6月) MachineLearningEng 博士 全职@Robinhood - 网上海投 - 技术电面  | Fail/Rej | 在职跳槽

地里side order题的简化版，可能是因为面ML的岗位，所以题更简单点。他家好像刚开始做ML，现在好像还在搭ML的平台，有一些ML的机会吧。

给一堆股票的transaction，比如
[ {‘symbol’: ‘FB’, ‘side’: ‘buy’, ‘quantity’: 1, ‘price’: 200},
{‘symbol’: ‘AAPL’, ‘side’: ‘buy’, ‘quantity’: 1, ‘price’: 100},
{‘symbol’: ‘FB’, ‘side’: ‘sell’, ‘quantity’: 1, ‘price’: 150},
{‘symbol’: ‘AAPL’, ‘side’: ‘buy’, ‘quantity’: 1, ‘price’: 200},
{‘symbol’: ‘AAPL’, ‘side’: ‘buy’, ‘quantity’: 4, ‘price’: 150},
{‘symbol’: ‘AAPL’, ‘side’: ‘sell’, ‘quantity’: 1, ‘price’: 210},
{‘symbol’: ‘AAPL’, ‘side’: ‘sell’, ‘quantity’: 4, ‘price’: 220},
]
对于每一个sell，使用FIFO规则，输出没一个sell的信息，包括capital gain
比如上面例子的输出
[
{‘symbol’: ‘FB’, ‘quantity’: 1, ‘capital gain’: -50},
{‘symbol’: ‘AAPL’, ‘quantity’: 1, ‘capital gain’: 110},
{‘symbol’: ‘AAPL’, ‘quantity’: 1, ‘capital gain’: 20},
{‘symbol’: ‘AAPL’, ‘quantity’: 3, ‘capital gain’: 210},
]
说时间复杂度的时候刚开始说错了，后来提醒下才意识到是O(n)。
Follow up: 如果不用FIFO，每一个sell match之前最低的价格来maximize capital gain
然后自己想test cases来测试
整体感觉聊得挺开心的，题也全写完了，面试官也一直认可我的回答，然后就挂了，可能是时间复杂度那里没说对吧。

 My Solution:
 Buy:
   map<string, vector<int, int>> or map<string, set<int, int>>
   sym => price=> quantity
 Sell:
   sym =>
*/




#endif // PNSEI_CAPITAL_GAIN_H
