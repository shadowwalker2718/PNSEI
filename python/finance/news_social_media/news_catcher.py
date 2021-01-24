from newscatcher import Newscatcher

nc = Newscatcher(website = 'nytimes.com')
results = nc.get_news()

# results.keys()
# 'url', 'topic', 'language', 'country', 'articles'

# Get the articles
articles = results['articles']

first_article_summary = articles[0]['summary']
first_article_title = articles[0]['title']

print(articles)
