from requests import Session

cookies = {
    'next-auth.csrf-token': '11827d9fd09f39b1221901d454a10ccca689427e2fad37657c97e5d673898560%7C8fd92da011a1bc84dde0b0727b6f158fbf6bee6639e4890c012ba319b44fc30a',
    'next-auth.callback-url': 'http%3A%2F%2Flocalhost%3A3000%2F',
}

headers = {
    'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/119.0',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8',
    'Accept-Language': 'en-US,en;q=0.5',
    # 'Accept-Encoding': 'gzip, deflate, br',
    'Connection': 'keep-alive',
    # 'Cookie': 'next-auth.csrf-token=11827d9fd09f39b1221901d454a10ccca689427e2fad37657c97e5d673898560%7C8fd92da011a1bc84dde0b0727b6f158fbf6bee6639e4890c012ba319b44fc30a; next-auth.callback-url=http%3A%2F%2Flocalhost%3A3000%2F',
    'Upgrade-Insecure-Requests': '1',
    'Sec-Fetch-Dest': 'document',
    'Sec-Fetch-Mode': 'navigate',
    'Sec-Fetch-Site': 'none',
    'Sec-Fetch-User': '?1',
}

session = Session()
response = session.get('http://localhost:9000/', cookies=cookies, headers=headers)
session.close()
