# https://www.1point3acres.com/bbs/interview/software-engineer-648182.html


https://zhuanlan.zhihu.com/p/89570096

今日头条使用MySQL或Mongo持久化存储+Memched（Redis），分了很多库（一个大内存库），亦尝试使用了SSD的产品。
今日头条的图片存储，直接放在数据库中，分布式保存文件，读取的时候采用CDN。