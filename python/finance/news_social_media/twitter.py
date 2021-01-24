import json
from kafka import KafkaProducer, KafkaClient
import tweepy
import configparser


class TweeterStreamListener(tweepy.StreamListener):
    """ A class to read the twitter stream and push it to Kafka"""

    def __init__(self, api):
        self.api = api
        super(tweepy.StreamListener, self).__init__()
        #client = KafkaClient(cluster=["localhost:9092"])
        #self.producer = KafkaProducer(client, batch_send_every_n=1000, batch_send_every_t=10)

    def on_status(self, status):
        """ This method is called whenever new data arrives from live stream.
        We asynchronously push this data to kafka queue"""
        msg = status.text.encode('utf-8')
        try:
            #self.producer.send_messages(b'twitterstream', msg)
            print(msg)
        except Exception as e:
            print(e)
            return False
        return True

    def on_error(self, status_code):
        print(f"Error: {status_code}")
        return True  # Don't kill the stream

    def on_timeout(self):
        return True  # Don't kill the stream

if __name__ == '__main__':
    auth = tweepy.OAuthHandler("RpLtCj0bT8LdT0Gru0LJmw6nT",
                               "p4AM3kvqapmrGnEYXDwCSpLEOso86Ki4TdWZiznH3YexXH1w3L")
    auth.set_access_token('14072947-Bs5MuP5sY1mx7mHLIvFykWvWqvxLk78jddRUcFW7W',
                          'T7yY4k6OHrgkqXPLMa770YQsZZ9dY8k0WJlrsFF5wR92m')
    api = tweepy.API(auth, wait_on_rate_limit=True, wait_on_rate_limit_notify=True)

    """
    public_tweets = api.home_timeline()
    for tweet in public_tweets:
        print(tweet.text)
    """
    # Create stream and bind the listener to it
    listener = TweeterStreamListener(api)
    stream = tweepy.Stream(auth, listener=listener)

    # Custom Filter rules pull all traffic for those filters in real time.
    stream.filter(track = ['TSLA'])
    # stream.filter(locations=[-180, -90, 180, 90], languages=['en'])


