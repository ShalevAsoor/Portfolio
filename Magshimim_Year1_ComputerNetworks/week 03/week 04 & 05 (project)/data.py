DOTS = "..."  # A constant representing ellipsis
ALBUM_SPLIT = "#"  # Separator for album entries in the file
SONG_SPLIT = "*"  # Separator for song entries within an album
DETAILS_SPLIT = "::"  # Separator for song details within a song entry
DETAILS_SEPERATOR = "--"  # Separator for individual song details
LYRICS_PLACE = 2  # Index of lyrics in the song details

def pinkFloyd():
    '''
    This function reads the "Pink_Floyd_Db.txt" file and extracts the data into a dictionary of albums and songs.
    '''

    file = open("Pink_Floyd_Db.txt", "r")
    f_c = file.read()

    albSplit = f_c.split(ALBUM_SPLIT)
    albSplit.remove('')

    albums = {}
    songs = {}
    sngDetails = []

    for i in range(len(albSplit)):
        x = albSplit[i].split('\n')
        albName = x[0]
        x = albSplit[i].split(SONG_SPLIT)
        songs = {}

        for i in range(len(x)):
            if x[i] != albName + ('\n'):
                sngDetails = x[i].split(DETAILS_SPLIT)
                sngName = sngDetails[0]
                artist = sngDetails[1]
                time = sngDetails[LYRICS_PLACE]
                lyrics = sngDetails[3]
                details = artist + DETAILS_SEPERATOR + \
                    time + DETAILS_SEPERATOR + lyrics
                details = details.split(DETAILS_SEPERATOR)
                songs[sngName] = details

        albums[albName] = songs

    file.close()

    return albums


albums = pinkFloyd()


def one(albums):
    '''
    Returns a list of all album names.
    '''
    albumList = []
    for i in albums.keys():
        albumList.append(i)
        # Removes the year from the album name
        a, b, c = albumList[albumList.index(i)].partition('::')
        albumList[albumList.index(i)] = a

    return albumList


def two(albums, request):
    '''
    Returns a string containing all the songs from a specific album.
    '''

    # Handle album name correction for cases where the year is included in the name
    if request == "The Piper At The Gates Of Dawn":
        request = "The Piper At The Gates Of Dawn::1967"
    elif request == "A Saucerful of Secrets":
        request = "A Saucerful of Secrets::1968"
    elif request == "More":
        request = "More::1969"
    elif request == "Division Bell":
        request = "Division Bell::1994"
    elif request == "The Wall":
        request = "The Wall::1979"
    elif request == "Dark side of the moon":
        request = "Dark side of the moon::1973"
    elif request == "Wish you were here":
        request = "Wish you were here::1975"
    elif request == "Animals":
        request = "Animals::1977"

    songs = []
    for key in albums[request].keys():
        songs.append(key)

    songs = ', '.join(songs)

    return songs


def three(albums, request):
    '''
    Returns the length of a song.
    '''
    album = ''
    for i in albums.keys():
        if request in albums[i]:
            album = i

    print(albums[album][request][1])
    return albums[album][request][1]


def four(albums, request):
    '''
    Returns the lyrics of the entered song.
    '''
    album = ''
    for i in albums.keys():
        if request in albums[i]:
            album = i

    print(albums[album][request][LYRICS_PLACE])
    return albums[album][request][LYRICS_PLACE]


def five(albums, request):
    '''
    Returns the album that contains the entered song.
    '''
    albumList = []
    album = ''
    for i in albums.keys():
        if request in albums[i]:
            album = i
        a, b, c = album.partition('::')
        album = a

    print(album)
    return album


def six(albums, request):
    '''
    Returns all the songs that have the entered word in their name.
    '''
    songs = []
    for i in albums.keys():
        for j in albums[i].keys():
            if str(request).lower() in j.lower():
                songs.append(j)
    songs = ', '.join(songs)
    print(songs)
    return songs


def seven(albums, request):
    '''
    Returns all the songs that have the entered word in their lyrics.
    '''
    songs = []
    for i in albums.keys():
        for j in albums[i].keys():
            if str(request).lower() in str(albums[i][j][LYRICS_PLACE]).lower():
                songs.append(j)
    songs = ', '.join(songs)
    print(songs)
    return songs
