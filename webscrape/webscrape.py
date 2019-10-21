#!/usr/bin/env python3
import webbrowser as web
import requests
from bs4 import BeautifulSoup

def scrape_text(url, soup_select, index):
    page = requests.get(url)
    html = page.text
    soup = BeautifulSoup(html, 'html.parser')
    obj = soup.select(soup_select)[index]
    return obj.getText()

## EXAMPLE BREAKDOWN OF COMMANDS
#get url
#weatherpage = requests.get(url)
#get text from page
#html = weatherpage.text
#pass it into a Soup object
#soup = BeautifulSoup(html, 'html.parser')
#parse the html
#first get div with id #current_conditions-summary, then get all p elements within that div
#then get the second p element with [1]
#these are commands seperated by spaces
#temps = soup.select('div #current_conditions-summary p')[1]
#then get the text in that p element
#WH_temp = temps.getText()

##WEATHER
wdland_url = 'https://forecast.weather.gov/MapClick.php?CityName=Woodland+Hills&state=CA&site=LOX&textField1=34.1683&textField2=-118.605&e=0#.XSWr6OhKiUl'

weather_select = 'div #current_conditions-summary p'

Wdland_Hills = scrape_text(wdland_url, weather_select, 1)
                           
print('Right now, it is', Wdland_Hills, 'in Woodland Hills, CA.')

okc_url = 'https://forecast.weather.gov/MapClick.php?lat=35.39312000000007&lon=-97.60086999999999#.XSxaOuhKiUk'

okc = scrape_text(okc_url, weather_select, 1)

print('Right now, it is', okc, 'in Oklahoma City, OK.')

##SMASH
smashurl = "https://www.elitegsp.com/"
smash_select = 'div #gsp_average_number'
smash_gsp = scrape_text(smashurl, smash_select, 0)

print("Also, average gsp for elite smash is",smash_gsp)



