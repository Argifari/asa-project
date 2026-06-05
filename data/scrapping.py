import requests
from bs4 import BeautifulSoup
import json

url = "https://www.dustloop.com/wiki/index.php?title=GGST/Sol_Badguy/Frame_Data"
response = requests.get(url)
soup = BeautifulSoup(response.text, 'html.parser')

solMoves = []

tables = soup.find_all('table', class_='wikitable')

for table in tables:
    rows = table.find_all('tr')
    for row in rows[1:]:
        cols = row.find_all('td')
        if len(cols) >= 5 :
            moveData = {
                "moveName": cols[0].text.strip(),
                "damage": cols[1].text.strip(),
                "startupFrame": cols[2].text.strip(),
                "activeFrame": cols[3].text.strip(),
                "recoveryFrame": cols[4].text.strip(),
            }
            solMoves.append(moveData)

with open('solData.json','w') as f:
    json.dump(solMoves,f,indent=4)

print(f"Berhasil mengambil {len(solMoves)} gerakan Sol Badguy!")