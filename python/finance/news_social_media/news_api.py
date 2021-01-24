# https://newsapi.org/docs/get-started

from newsapi import NewsApiClient

API_key='146a6b89184d46dd86447f24374f3506'


# Init
newsapi = NewsApiClient(api_key=API_key)

# /v2/top-headlines
top_headlines = newsapi.get_top_headlines(q='bitcoin',
                                          sources='bbc-news,the-verge',
                                          language='en')

# /v2/everything
all_articles = newsapi.get_everything(q='bitcoin',
                                      sources='bbc-news,the-verge',
                                      domains='bbc.co.uk,techcrunch.com',
                                      from_param='2020-12-01',
                                      to='2020-12-25',
                                      language='en',
                                      sort_by='relevancy',
                                      page=2)

# /v2/sources
sources = newsapi.get_sources()

