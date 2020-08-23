package practice.instacart;
/*
2. System: Payment service for shopper. 楼主花了好久的时间才意识到customer和shopper不是一个概念，估计会挂在这一轮。。。
Problem

At Instacart, we have customers that place orders on our website, and we hire personal shoppers whose
job it is to go to grocery stores to fulfill those orders.

We give credit cards to our shoppers so they can purchase groceries for orders we've assigned them. Our
 servers receive an HTTP request from our payment processor every time a shopper swipes the credit card
  that we give them. The payload looks like this:

{
    shopper_id:  123，
    amount: 300,
    merchant: {
        name: "Target",
        address: "123 Main St"
    }
}

When we receive the HTTP request, we have to synchronously respond within 1 second with a 200 OK to
 approve the transaction or 402 Payment Required to decline the transaction.

Say you are hired tomorrow, and you're leading the three person team in this room.  How would you
suggest we build the application that processes these requests? Some areas we should be sure to cover are:

- physical infrastructure
- data stores
- data model
- security
- performance considerations

For simplicity, we should start off with the assumption that 1 Shopper has just 1 Order at 1 merchant.

* */
public class PaymentService {
}
