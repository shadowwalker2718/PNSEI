# pip install GoogleNews
# https://medium.com/analytics-vidhya/googlenews-api-live-news-from-google-news-using-python-b50272f0a8f0

from GoogleNews import GoogleNews
googlenews = GoogleNews()

googlenews = GoogleNews(lang='en')
googlenews = GoogleNews(period='7d')

googlenews.get_news('APPLE')
news_apple=googlenews.get_texts()

print(news_apple)

