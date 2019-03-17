import pandas as pd 
import spotipy 

sp = spotipy.Spotify() 

########### SLOW DOWN ####################
from spotipy.oauth2 import SpotifyClientCredentials 
cid ="client id" 
secret = "secret" 
client_credentials_manager = SpotifyClientCredentials(client_id=cid, client_secret=secret) 
sp = spotipy.Spotify(client_credentials_manager=client_credentials_manager) 
sp.trace=False 
aux = 0;
df = pd.DataFrame()
for i in range(8):
    playlist = sp.user_playlist_tracks("-", "-", limit = 100, offset = aux) 
    songs = playlist["items"]
    ids = [] 
    for i in range(len(songs)): 
        ids.append(songs[i]["track"]["id"]) 
    features = sp.audio_features(ids) 
    df1 = pd.DataFrame(features)
    df = df.append(df1, ignore_index=True)
    aux = aux + 100
    
df['class'] = pd.Series(1, index=df.index)


########### ROCKZ ####################
from spotipy.oauth2 import SpotifyClientCredentials 
cid ="client id" 
secret = "secret" 
client_credentials_manager = SpotifyClientCredentials(client_id=cid, client_secret=secret) 
sp = spotipy.Spotify(client_credentials_manager=client_credentials_manager) 
sp.trace=False 
aux = 0;
for i in range(2):
    playlist = sp.user_playlist_tracks("-", "-", limit = 100, offset = aux) 
    songs = playlist["items"]
    ids = [] 
    for i in range(len(songs)): 
        ids.append(songs[i]["track"]["id"]) 
    features = sp.audio_features(ids) 
    df1 = pd.DataFrame(features)
    df1['class'] = pd.Series(1, index=df.index)
    df = df.append(df1, ignore_index=True)
    aux = aux + 100
 

################### HATE ##########################
from spotipy.oauth2 import SpotifyClientCredentials 
cid ="client id" 
secret = "secret" 
client_credentials_manager = SpotifyClientCredentials(client_id=cid, client_secret=secret) 
sp = spotipy.Spotify(client_credentials_manager=client_credentials_manager) 
sp.trace=False 
aux = 0;
for i in range(7):
    playlist = sp.user_playlist_tracks("-", "-", limit = 100, offset = aux) 
    songs = playlist["items"]
    ids = [] 
    for i in range(len(songs)): 
        ids.append(songs[i]["track"]["id"]) 
    features = sp.audio_features(ids) 
    df1 = pd.DataFrame(features)
    df1['class'] = pd.Series(0, index=df.index)
    df = df.append(df1, ignore_index=True)
    aux = aux + 100
    
    
df = df.sample(frac=1).reset_index(drop=True)
df.to_csv("data.csv", index_label=False, encoding='utf-8')
