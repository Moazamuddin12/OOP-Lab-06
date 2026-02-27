#include <iostream>
#include <cstring>
using namespace std;

class Song {
private:
    char* songTitle;
    char* songArtist;
    int songDuration;
    int songRating;

public:
    Song(const char* title = "", const char* artist = "", int duration = 0, int rating = 0) {
        songTitle = new char[strlen(title) + 1];
        strcpy(songTitle, title);

        songArtist = new char[strlen(artist) + 1];
        strcpy(songArtist, artist);

        songDuration = duration;
        songRating = rating;
    }

    Song(const Song& Scopy) {
        songTitle = new char[strlen(Scopy.songTitle) + 1];
        strcpy(songTitle, Scopy.songTitle);

        songArtist = new char[strlen(Scopy.songArtist) + 1];
        strcpy(songArtist, Scopy.songArtist);

        songDuration = Scopy.songDuration;
        songRating = Scopy.songRating;
    }

    ~Song() {
        delete[] songTitle;
        delete[] songArtist;
    }

    int getDuration() const { return songDuration; }
    int getRating() const { return songRating; }
    void setRating(int rating) { if (rating >= 0 && rating <= 5) songRating = rating; }

    void display() const {
        cout << songTitle << " - " << songArtist << " - " << songDuration << "s - Rating: " << songRating << endl;
    }
};

class Playlist {
private:
    char* playlistName;
    Song** playlistSongs;
    int numberOfSongs;
    int playlistCapacity;

public:
    Playlist(const char* name, int capacity = 10) {
        playlistName = new char[strlen(name) + 1];
        strcpy(playlistName, name);

        playlistCapacity = capacity;
        numberOfSongs = 0;

        playlistSongs = new Song*[playlistCapacity];
        for (int i = 0; i < playlistCapacity; i++)
            playlistSongs[i] = nullptr;
    }

    Playlist(const Playlist& Pcopy) {
        playlistName = new char[strlen(Pcopy.playlistName) + 1];
        strcpy(playlistName, Pcopy.playlistName);

        playlistCapacity = Pcopy.playlistCapacity;
        numberOfSongs = Pcopy.numberOfSongs;

        playlistSongs = new Song*[playlistCapacity];
        for (int i = 0; i < numberOfSongs; i++)
            playlistSongs[i] = new Song(*(Pcopy.playlistSongs[i]));

        for (int i = numberOfSongs; i < playlistCapacity; i++)
            playlistSongs[i] = nullptr;
    }

    ~Playlist() {
        for (int i = 0; i < numberOfSongs; i++)
            delete playlistSongs[i];
        delete[] playlistSongs;
        delete[] playlistName;
    }

    void addSong(const Song& songToAdd) {
        if (numberOfSongs == playlistCapacity) {
            playlistCapacity *= 2;
            Song** newPlaylistSongs = new Song*[playlistCapacity];

            for (int i = 0; i < numberOfSongs; i++)
                newPlaylistSongs[i] = playlistSongs[i];

            for (int i = numberOfSongs; i < playlistCapacity; i++)
                newPlaylistSongs[i] = nullptr;

            delete[] playlistSongs;
            playlistSongs = newPlaylistSongs;
        }

        playlistSongs[numberOfSongs] = new Song(songToAdd);
        numberOfSongs++;
    }

    void rateSong(int songIndex, int newRating) {
        if (songIndex >= 0 && songIndex < numberOfSongs)
            playlistSongs[songIndex]->setRating(newRating);
    }

    double calculateAverageRating() const {
        if (numberOfSongs == 0) return 0;

        int sumRatings = 0;
        for (int i = 0; i < numberOfSongs; i++)
            sumRatings += playlistSongs[i]->getRating();

        return (double)sumRatings / numberOfSongs;
    }

    int calculateTotalDuration() const {
        int totalDuration = 0;
        for (int i = 0; i < numberOfSongs; i++)
            totalDuration += playlistSongs[i]->getDuration();
        return totalDuration;
    }

    void displayPlaylist() const {
        cout << "===== PLAYLIST: " << playlistName << " =====" << endl;
        for (int i = 0; i < numberOfSongs; i++) {
            cout << i + 1 << ". ";
            playlistSongs[i]->display();
        }
        cout << "Average Rating: " << calculateAverageRating() << " stars" << endl;
        cout << "Total Duration: " << calculateTotalDuration() << " seconds" << endl;
    }
};

int main() {
    Song mainLibrary[4] = {
        Song("Blinding Lights", "The Weeknd", 200),
        Song("Shape of You", "Ed Sheeran", 233),
        Song("Bohemian Rhapsody", "Queen", 354),
        Song("Stay", "Justin Bieber", 140)
    };

    cout << "===== MAIN LIBRARY =====" << endl;
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". ";
        mainLibrary[i].display();
    }
    cout << endl;

    Playlist myFavoritesPlaylist("My Favorites");
    myFavoritesPlaylist.addSong(mainLibrary[0]);
    myFavoritesPlaylist.addSong(mainLibrary[2]);
    myFavoritesPlaylist.rateSong(0, 5);
    myFavoritesPlaylist.displayPlaylist();
    cout << endl;

    Playlist myFavoritesPlaylistCopy(myFavoritesPlaylist);
    myFavoritesPlaylistCopy.rateSong(1, 4);

    cout << "===== PLAYLIST COPY: My Favorites (Copy) =====" << endl;
    myFavoritesPlaylistCopy.displayPlaylist();
    cout << endl;

    cout << "===== VERIFICATION =====" << endl;
    cout << "Main library songs unchanged:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". ";
        mainLibrary[i].display();
    }

    return 0;
}
