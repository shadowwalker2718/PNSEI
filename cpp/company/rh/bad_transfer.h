#ifndef PNSEI_BAD_TRANSFER_H
#define PNSEI_BAD_TRANSFER_H

/*
https://www.1point3acres.com/bbs/thread-653048-1-1.html

第二题是 bad transaction：

给了一个银行转账的伪代码，代码存在读写冲突问题，如下：

def bad_transfer(src_account, dst_account, amount):
    src_cash = src_account.cash # DB read
    dst_cash = dst_account.cash # DB read

    if src_cash < amount:
        raise InsufficientFunds

    src_account.cash = src_cash - amount # DB write
    src_account.send_src_transfer_email()
    dst_account.cash = dst_cash + amount # DB write
    dst_account.send_dst_transfer_email()

我回答的解决方法是代码加锁 (synchronized)，改变 DB 的隔离等级，
转账完成的邮件需要在转账完成之后再发送等（如果有错请指正）。

 My solution:

 def bad_transfer(src_account, dst_account, amount):
    if  src_account.id > dst_account.id:
      lock(src_account.mutex)
      lock(dst_account.mutex)
    else:
      lock(dst_account.mutex)
      lock(src_account.mutex)
    src_cash = src_account.cash # DB read
    dst_cash = dst_account.cash # DB read
    if src_cash < amount:
        raise InsufficientFunds
    src_account.cash = src_cash - amount # DB write
    dst_account.cash = dst_cash + amount # DB write

bad_transfer(a,b)
a.send_src_transfer_email()
b.send_dst_transfer_email()
*/

#endif // PNSEI_BAD_TRANSFER_H
