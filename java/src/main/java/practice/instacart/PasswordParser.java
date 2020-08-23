package practice.instacart;

/*
3. Coding：简单的parse in文件合成密码，最后问放在产品端怎么改进。
follow up是The chunks look the same as before, but now rather than a single
password the input contains a series of passwords, one following the other.
You will know one password has ended and the next begun when you see an index
repeated. Read only enough of the stream to find the first password and print it out.

https://www.glassdoor.co.nz/Interview/Consume-a-streaming-HTTP-feed-find-a-password-in-a-block-of-characters-with-some-provided-coordinates-QTN_2613218.htm

Instacart Interview Experience
Oct 23, 2019


This post is to share my interview experience with Instacart for a Senior Software Engineer
position in Toronto(June 2019). I was initially contacted by a recruiting agency who co-ordinated
the interview process.

Round 0 - Remote Coding
The first round was a 1 hour coding exercise on CoderPad with an Engineer from their San Francisco
office. The challenge was to implement a time-based key-value store similar to this Leetcode problem .
(The interviewer started off asking me to implement a simple key-value store, and moved on to the
more complex time-based variant). I (sort of)followed a TDD approach , writing test cases first,
confirming the expected behavior with the interviewer and then implementing and running the
solution on Coderpad. I was able to complete the solution without needing too much hints from
the interviewer , but I made sure to talk him through my approach while I’m coding.

He seemed happy with the solution and let me ask some questions about the company and work. He
then said I did good and mentioned that a recruiter will be reaching out to me for further steps.
I was actually attending this from India, and scheduled my onsite interviews once I landed in Toronto.

Round 1 - System Design
The first on-site round was with a couple of Senior developers and focused on System design. One
of the interviewers drew a simple architecture diagram for a payments application and asked the
following question:

Design a system to accept/reject payments

I asked some clarifying questions and jumped into describing a technical solution. Turns out, that was a mistake and the interviewers expected me to question more on the business flow and the entities involved in a payment transaction for an Instacart order(Customer, Grocery Picker, Instacart’s Order management system, Payment Gateway, etc ), describe a solution that would handle all business use cases before diving into the technical design and implementation.

May be it is a fair expectation, but most other companies I interviewed with focused on technical design and I wasn’t expecting Instacart to be any different - This was a good learning for me. As I got to know from the feedback, the interviewers felt I jumped too soon into the technical design and didn’t spend enough time understanding the business flow.

Round-2 - Behavioral
The next round was with an Engineering Manager, and it was the usual behavioral questions like the ones below:

Tell me about yourself

What is the most challenging project you have worked on?

What are some mistakes/failures from your last project?

What did you learn from the mistakes?

Who is the best developer you have worked with? Who do you model yourself after?

What are you looking for in your next workplace?

Where do you see yourself in the next 3 years?

The interviewer was very soft-spoken and extremely attentive, even making notes during the conversation.

Round 3 - Coding (on HackerRank)
The next round was with a Senior developer and involved solving a program/puzzle on hackerrank.
If I remember correctly, it was about implementing a Password cracker. It had 3 levels of
questions and you progress to a level by solving a question at the previous level. The
input is a 2D array of characters, the password can be built from the characters in the
2D array - the difficulty of building the password was higher as you move up the levels.
(If I remember correctly) For the first level, the input had 2 integers (lets say x and y),
and the password was the substring from index 0 to index y on row x.

The logic to derive the password becomes complex as the levels go up.

This seemed an interesting round, but what I did not like was the fact that I had to write all
 the boilerplate code to read all the input (characters of the 2D array, and the subsequent
 hints like the values of x and y) - I hadn’t done this on HackerRank recently, and got stuck
 with this weird behaviour of Scanner.nextInt() method in java while reading the input. The
 interviewer couldn’t help either since he wasn’t very familiar with Java and I ended up
 wasting more than 30 minutes trying to get my input reader working.

I was able to solve the 1st level but ran out of time before submitting my solution to the
2nd level - The interviewer looked at the code and seemed fine with it though. However, I was
a bit disappointed with myself(and the Scanner class 😄) for not completing this
seemingly-solvable exercise.

Round 4 - Coding
The 4th round was also a coding round with another Senior Developer. If I thought that 3
levels were crazy, I was wrong - This round had like 10 levels to be completed over HackerRank.
However, the interviewer mentioned that the expectation is not to complete all 10, but do
whatever possible within the allotted 50 minutes.

This round involved creating a Json request, invoking some REST APIs and extracting certain
values from the response and use it as a key to the next level. Similar to the previous round,
the Json request/response handling became complex as I moved up the levels. The requirements
were convoluted and unnecessarily hard to understand, but the interviewer was very helpful in
breaking it down for me.

I could use my IDE for this exercise, so I setup a new java project with maven and started
typing away. I used Jackson for json handling and Apache HTTP Client for making API calls -
Both these libraries required some boilerplate code and configuring the Jackson Object
mapper has always been a pain-point. Long story short, I completed 3 levels and ran out
of time before I could move on to the 4th level. My fingers were finally happy to get
some rest after some frantic typing 😄.

In hindsight, I felt Java was not a good choice for the exercise since I had to add multiple
third party dependencies and add many lines of boilerplate code to accomplish trivial things
(like calling an API, parsing the json response , etc) - It made me realize that I should
get stronger in a language other than Java and use the right language for a problem.

Final Thoughts
Hmm, where do I start? Instacart was my first experience interviewing in Canada (or anywhere
 outside India,
for that matter), and was wildly different from the other companies I had interviewed at.
Except the online
coding round , none of the rounds were focused on data-structures and algorithms which I
found surprising.
Also, I felt the exercises were designed to test a candidate’s ability to code fast (and
under time pressure).
I also felt handicapped using Java for these exercises and my life would’ve been so much
easier if I had used
a language like Ruby or Python (which are concise and would’ve let me do more with fewer
lines of code, plus
they have first-class support for Http requests and Json handling).

https://www.soberkoder.com/instacart-interview-experience-toronto/
*/

public class PasswordParser {
}
