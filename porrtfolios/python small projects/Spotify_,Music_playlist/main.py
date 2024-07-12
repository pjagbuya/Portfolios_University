from bs4 import BeautifulSoup
import lxml
import requests
import spotipy
from spotipy.oauth2 import SpotifyOAuth
from spotipy.oauth2 import SpotifyClientCredentials
import datetime
from tkinter import *
from tkinter import messagebox # Some modules are not included with *
from random import shuffle, randint, choice
import pyperclip
import json


SPOTIFY_USER_ID  = "elgnhqyjy3imlsvp5vv8nc2s9"
REDIRECT_URL = "https://reishor's_throwback_API.com/callback/"
SPOTIFY_CLIENT_ID = "d28b0b6fbf1d494ea769da563de7e433"
SPOTIFY_CLIENT_KEY = "3d0eaf4898c54248b68616996b35df73"


# SPOTIFY_CREATE_PLAYLIST_URL = f"https://api.spotify.com/v1/users/f{SPOTIFY_USER_ID}/playlists"
# SPOTIFY_CREATEPLAYLIST_PARAMETERS = {
#     "name": "Test Playlist",
#     "description": "New playlist description",
#     "public": False
# }
# SPOTIFY_CREATEPLAYLIST_HEADERS = {
#     "header": 'Authorization'
# }


"""----------------------------------------------------------------------------------------------------------------"""
def SPOTIFY_MACHINE():

    no_song_request = True

    while no_song_request:
        user_date = input("Which year do you want to time travel to? (please use this format 'YYYY-MM-DD') ")
        checklist = [char for char in user_date.split('-') if char.isnumeric()]
        if len(checklist) == len(user_date.split('-')):
            if len(checklist[0]) == 4 and len(checklist[1]) == 2 and len(checklist[2]) == 2:
                if int(checklist[0]) >= 2000:
                    pass
                else:
                    print("Error in year, please input music in the 2000s and above\n")
                if int(checklist[1].lstrip('0')) <= 12:
                    pass
                else:
                    print("Error in month, please input correct month input\n")

                if int(checklist[2].lstrip('0')) <= 31:
                    try:
                        datetime.datetime(year=int(checklist[0]), month=int(checklist[1].lstrip('0')),
                                      day=int(checklist[2].lstrip('0')))
                        no_song_request = False
                    except ValueError:
                        print(f"Your day doesn't seem to  exist, please check leap days and accurate existence of certain days in a month\n")

                else:
                    print("Error in day, please input correct day that exists\n")



            else:
                print("Error in your date formatting \n")

        else:
            print("Please put the recommended syntax\n")
            pass


    user_date_year = user_date.split('-')[0]


    response = requests.get(url=f"https://www.billboard.com/charts/hot-100/{user_date}/")
    soup = BeautifulSoup(response.text, "html.parser")

    PLAYLIST_NAME = "Throwback Machine to"

    SONG_NAMES = soup.select(selector=".o-chart-results-list-row-container .lrv-u-width-100p h3")
    SONG_LIST_FINAL = [item.getText().split('\t')[9] for item in SONG_NAMES]
    SONG_ARTISTS = soup.select(selector=".o-chart-results-list-row .lrv-u-width-100p ul li span")
    SONG_ARTISTS_FINAL = [item.getText().split("\t")[2].split("\n")[0] for item in SONG_ARTISTS]
    SONG_ARTISTS_FINAL = SONG_ARTISTS_FINAL[::7]

    sp = spotipy.Spotify(auth_manager=SpotifyOAuth(client_id=SPOTIFY_CLIENT_ID,
                                                   client_secret=SPOTIFY_CLIENT_KEY,
                                                   redirect_uri=REDIRECT_URL,
                                                   scope="playlist-modify-private"))

    SONG_ARTISTS_FINAL = [item.replace("&", "and")for item in SONG_ARTISTS_FINAL]
    PLAYLIST = sp.user_playlist_create(user=SPOTIFY_USER_ID, name=f"{PLAYLIST_NAME} {user_date}", description= f"Welcome to the year {user_date_year}", public=False)
    PLAYLIST_ID = PLAYLIST['id']
    SONGS_THROWBACK = []


    for item in SONG_LIST_FINAL:
        results = sp.search(q=f'{item}' + f', {SONG_ARTISTS_FINAL[SONG_LIST_FINAL.index(item)]}')
        try:
            for track in results['tracks']['items']:

                if track['name'].split(" ")[0].lower() == item.split(" ")[0].lower():
                    SONGS_THROWBACK.append(f"spotify:track:{track['id']}")
                    break
        except:
            pass
    sp.user_playlist_add_tracks(user=SPOTIFY_USER_ID, playlist_id=PLAYLIST_ID, tracks=SONGS_THROWBACK)


    print("Your requested playlist is done:")
    print(f"https://open.spotify.com/playlist/{PLAYLIST_ID}\n")
    user_try_again_invalid = True
    while user_try_again_invalid:
        user_try_again = input("Would you like to make a playlist again? (Y/N): ")
        if user_try_again.replace(" ", "").upper() == 'Y':
            user_try_again_invalid = False
            SPOTIFY_MACHINE()
        elif user_try_again.replace(" ", "").upper() == 'N':
            user_try_again_invalid = False
            exit()
        else:
            print("Error in your input, please only type 'Y' or  'N' in the input prompt")
SPOTIFY_MACHINE()





"""----------------------------------------------------------------------------------------------------------------"""

# results = sp.search(q='track:' + f'Incomplete', type='track')
# SONGS_THROWBACK.append(f"spotify:track:{results['tracks']['items'][0]['id']}")
# sp.user_playlist_add_tracks(user=SPOTIFY_USER_ID, playlist_id=PLAYLIST_ID, tracks=SONGS_THROWBACK)



# while playlists:
#     for i, playlist in enumerate(playlists['items']):
#         print("%4d %s %s" % (i + 1 + playlists['offset'], playlist['uri'],  playlist['name']))
#     if playlists['next']:
#         playlists = sp.next(playlists)
#     else:
#         playlists = None

# sp = spotipy.Spotify(auth_manager=SpotifyClientCredentials(client_id=SPOTIFY_CLIENT_ID,
#                                                            client_secret=SPOTIFY_CLIENT_KEY))
#
# results = sp.search(q=f'{SONG_LIST_FINAL[0]}', limit=20)
# for idx, track in enumerate(results['tracks']['items']):
#     print(idx, track['name'])
