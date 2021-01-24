import datetime

from polygon import RESTClient
import pymysql
import datetime



def get_dates():
    dates = []
    end_date = datetime.datetime.now().strftime('%Y-%m-%d')
    for i in range(30, 365 * 10, 30):
        from_date = (datetime.datetime.now() - datetime.timedelta(days=i)).strftime('%Y-%m-%d')
        dates.append((from_date, end_date))
        end_date = from_date
    return dates


dates = get_dates()

# Open database connection
# db = pymysql.connect("www.quant365.com","henrywu","password","sentosa")
db = pymysql.connect("localhost", "root", "Wufuheng1234!", "sentosa")

# prepare a cursor object using cursor() method
cursor = db.cursor()

# execute SQL query using execute() method.
cursor.execute("SELECT VERSION()")

# Fetch a single row using fetchone() method.
data = cursor.fetchone()
print("Database version : %s " % data)

# Pre-market trading in stocks occurs from 4 a.m. to 9:30 a.m. EST, and after-hours trading on a day with a normal session takes place from 4 p.m. to 8 p.m.
import time

offset = time.timezone if (time.localtime().tm_isdst == 0) else time.altzone
offset = offset - 18000


def ts_to_datetime(ts) -> str:
    return datetime.datetime.fromtimestamp(ts / 1000.0 + offset).strftime('%Y-%m-%d %H:%M:%S')


def main():
    key = "AK7ZO195L18ASY14JYGP"
    # RESTClient can be used as a context manager to facilitate closing the underlying http session
    # https://requests.readthedocs.io/en/master/user/advanced/#session-objects
    symbols = ['ABB', 'ADI', 'ADP', 'ADSK', 'AMAT', 'AMT', 'ANTM', 'APD', 'ATVI', 'BAM', 'BDX',
              'BIDU', 'BKNG', 'BSBR', 'BTI', 'CAT', 'CB', 'CCI', 'CI', 'CL', 'CME', 'CNI', 'CSX',
              'D', 'DE', 'DELL', 'DEO', 'DG', 'DUK', 'ECL', 'EL', 'EQIX', 'EW', 'FDX',
              'FIS', 'FISV', 'GILD', 'GPN', 'HCA', 'HUM', 'ICE', 'ILMN', 'INFY', 'ISRG', 'ITUB', 'ITW', 'LMT', 'LRCX',
              'MCO', 'MDLZ', 'MELI', 'MMC', 'MO', 'MU', 'NIO', 'NSC', 'NTES', 'PBR', 'PGR', 'PLD', 'RACE', 'REGN',
              'RIO', 'SCHW', 'SE', 'SHW', 'SNAP', 'SO', 'SPGI', 'SPOT', 'SYK', 'TEAM', 'TGT', 'TJX', 'TWLO', # 'UBER',
              'UBS', 'VALE', 'VMW', 'VRTX', 'WDAY', 'ZTS']
    for symbol in symbols:
        for from_, to in dates:
            count = 0
            with RESTClient(key) as client:
                resp = client.stocks_equities_aggregates(symbol, 1, "minute", from_, to, unadjusted=False, limit=50000)
                if resp.resultsCount == 0:
                    print("Error: ", symbol, from_, to)
                    break
                #print(f"Minute aggregates for {resp.ticker} between {from_} and {to}. Len: {len(resp.results)}")
                for result in resp.results:
                    dt = ts_to_datetime(result["t"])
                    # print(f"{dt}\tO: {result['o']}\tH: {result['h']}\tL: {result['l']}\tC: {result['c']} ")
                    if 'vw' not in result:
                        result['vw'] = result['o']
                    """cursor.execute("SELECT COUNT (*) FROM bar1m where s='{symbol}' and dt='{dt}' and o>0")
                    rowcount = cursor.fetchone()[0]
                    if rowcount == 1:
                        continue"""
                    sql = f"insert ignore into bar1m(s,o,h,l,c,v,w,bc,dt)VALUES('{symbol}',{result['o']},{result['h']},{result['l']},{result['c']},{result['v']},{result['vw']},-1,'{dt}')"
                    # print(f"sql: {sql}")
                    cursor.execute(sql)
                    count += 1
                    if count % 2500 == 1:
                        print("Status: ", symbol, from_, to, "| ", sql)
                        db.commit()
                db.commit()


if __name__ == '__main__':
    main()
    db.close()
