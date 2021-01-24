import os

dev_mode = True

if dev_mode:
    os.environ["APCA_API_KEY_ID"] = "PK02ZY7O3JNKJCJBJ4GG"
    os.environ["APCA_API_SECRET_KEY"] = "cSZanpBZz1AwweJg1PNswDcuZLfcbViQASgee5pu"
    os.environ["APCA_API_BASE_URL"] = "https://paper-api.alpaca.markets"
else:
    os.environ["APCA_API_KEY_ID"] = "AK7ZO195L18ASY14JYGP"
    os.environ["APCA_API_SECRET_KEY"] = "9Il1fu8OhrqAfSRFTke0T6XuMmwSSLEJ1tUnhib6"
    os.environ["APCA_API_BASE_URL"] = "https://api.alpaca.markets"
