//Martha Sander - Class songList implementation.

#include "songList.h"

//SongList constructors.
SongList::SongList()
{
	head = NULL;
	size = 0;
}

SongList::SongList(char fileName[])
{
	ifstream inFile;
	char artistInput[MAX], titleInput[MAX], albumInput[MAX];
	int minInput = 0, secInput = 0;
	Song mySong;
	
	head = NULL;
	size = 0;

	inFile.open(fileName);
	if (! inFile.is_open())
	{
		cout << "File is not open. Please review information and try again." << endl;
		exit(0);
	}
	cout << "file " << fileName << " successfully opened!" << endl << endl;
	inFile.get(titleInput, MAX, ';');
	inFile.ignore (100, ';');
	inFile.get(artistInput, MAX, ';'); 
	inFile.ignore (100, ';');
	inFile >> minInput;
	inFile.ignore (100, ';');
	inFile >> secInput;
	inFile.ignore(100, ';');
	inFile.get(albumInput, MAX, '\n');
	inFile.ignore(100, '\n');
	//add information to song.
	mySong.setTitle(titleInput);
	mySong.setArtist(artistInput);
	mySong.setMin(minInput);
	mySong.setSec(secInput);
	mySong.setAlbum(albumInput);

	while(!inFile.eof())
	{
		//add information to list.
		size++;
		addSong(mySong);
		inFile.get(titleInput, MAX, ';');
		inFile.ignore (100, ';');
		inFile.get(artistInput, MAX, ';'); 
		inFile.ignore (100, ';');
		inFile >> minInput;
		inFile.ignore (100, ';');
		inFile >> secInput;
		inFile.ignore(100, ';');
		inFile.get(albumInput, MAX, '\n');
		inFile.ignore(100, '\n');
		mySong.setTitle(titleInput);
		mySong.setArtist(artistInput);
		mySong.setMin(minInput);
		mySong.setSec(secInput);
		mySong.setAlbum(albumInput);
	}
	inFile.close();
}

void SongList::addSong(const Song &mySong)
{
	Node *temp = NULL, *temp2 = NULL;
	Node *newNode = NULL;

	char str1[MAX], str2[MAX];

	//get information into new node.
    newNode = new Node;
	newNode->data.setSong(mySong);
	mySong.getTitle(str1);
 	newNode->next = NULL;

    //if list is empty
 	if(!head)
    {
	    head = newNode;
		size++;
		return;
    }
  
	temp = head;

	//check is list has one node only;
	if(!head->next)
	{
		temp->data.getTitle(str2);
		if ((strcasecmp(str1, str2) < 0))
		{
			newNode->next = head;
			head = newNode;
		}
		else
		{
			head->next = newNode;
			newNode->next = NULL;
		}

		size++;
		return;
	}			
	
	temp2 = head;
	temp = temp->next;

	//if song title has to be added before head.
	head->data.getTitle(str2);
	if ((strcasecmp(str1, str2) < 0))
	{
		newNode->next = head;
		head = newNode;
		size++;
		return;
	}

	while (temp) 
	{
		//if newnode needs to be added to the end of the list.
		if(!temp->next)
		{
			temp->data.getTitle(str2);
			if((strcasecmp(str1, str2) < 0))
			{
				newNode->next = temp;
				temp2->next = newNode;
				size++;
				return;
			}	
			else
			{
				temp->next = newNode;
				size++;
				return;
			}
		}
		//adding node in the midlle of the list.
		temp->data.getTitle(str2);
		if ((strcasecmp(str1, str2) < 0))
		{
			//add song.
			temp2->next = newNode;
			newNode->next = temp;
			size++;
			return;
		}
		temp2 = temp;
		temp = temp->next;
	}	
}

//SongList destructor.
SongList::~SongList()
{
	Node *temp;
	temp = head;

	while(temp)
	{
		head = temp->next;
		delete temp;
		temp = head;
	}
}	

int SongList::getSize()
{
	return size;
}

void SongList::searchByArtist(char returnArtist[])
{
	char artistInput[MAX];
	int count = 0;
	int index = 1;
	Node *temp = head;	

	cout << "Search artist name: ";
	cin.getline(artistInput, MAX, '\n');

	while(temp)
	{
		temp->data.getArtist(returnArtist);
		if (strcasestr(returnArtist, artistInput))
		{
			count++;
			cout << "*********************" << endl;
			cout << "Index: " << index;
			temp->data.printSong();
			cout << endl;
		}
		temp = temp->next;
		index++;
	}
	if (count == 0)
		cout << "No songs by " << artistInput << " on your library." << endl;
}
void SongList::searchByAlbum(char returnAlbum[])
{
	char albumInput[MAX];
	int count = 0;
	Node *temp = head;	

	cout << "Search album name: ";
	cin.getline(albumInput, MAX, '\n');

	while(temp)
	{
		temp->data.getAlbum(returnAlbum);
		if (strcasestr(returnAlbum, albumInput))
		{
			count++;
			cout << "*********************" << endl;
			temp->data.printSong();
			cout << endl;
		}
		temp = temp->next;
	}
	if (count == 0)
		cout << "No songs for album " << albumInput << " on your library." << endl;
}

void SongList::printAllSongs()
{
	Node *temp;
	temp = head;
	int count = 1;

	cout << "These are all the songs in your library:" << endl;
	
	while(temp)
	{	
		cout << "************************" << endl;
		cout << "Index: " << count << endl;
		temp->data.printSong();
		cout << "************************" << endl;
		temp = temp->next;
		count++;
	}
}

void SongList::removeSong()
{
	int userIndex, index = 1;
	Song mySong;
	Node *temp = head, *temp2 = NULL;

	cout << "Please enter index of the song to be removed: ";
	cin >> userIndex;
	userIndex;
	
	if (userIndex > size)
	{
		cout << "No song at index selected. Please try again!" << endl;
		return;
	}
	
	cout << "Removing song at index " << userIndex << endl << endl;

	//list has only one node.
	if (!head->next)
	{
		head = NULL;
		size--;
		return;
	}
	
	//if song to be deleted is at the first node.
	if (userIndex == 1)
	{
		temp = head->next;
		delete head;
		head = temp;
		size--;
		return;
	}
	//removing last node of the list.
	temp2 = temp;
	temp = temp->next;
	index++;

	if (!temp->next)
	{
		temp2->next = NULL;
		delete temp;
		size--;
		return;
	}	
	//removing song at the midlle of the list.
	while (temp)
	{
		if (userIndex == index)
		{
			temp2->next = temp->next;
			delete temp;
			size--;
			return;	
		}
		temp2 = temp;
		temp = temp->next;
		index++;
	}
	cin.ignore(MAX, '\n');
}

void SongList::saveFile(char fileName[], char returnTitle[], char returnArtist[], char returnAlbum[])
{
	ofstream outFile;
	int min, sec;
	Node *temp;
	temp = head;

	outFile.open(fileName);
	if (! outFile.is_open())
	{
		cout << "file is not open. Please review information and try again." << endl;
		exit(0);
	}
	else
	{
		while (temp)
		{
			temp->data.getTitle(returnTitle);
			outFile << returnTitle << ";";
			temp->data.getArtist(returnArtist);
			outFile << returnArtist << ";";
			min = temp->data.getMin();
			outFile << min << ";"; 
			sec = temp->data.getSec();
			outFile << sec << ";";
			temp->data.getAlbum(returnAlbum);
			outFile << returnAlbum << endl;
		
			temp = temp->next;
		}
	}
	cout << endl;
	cout << "Library saved!" << endl << endl;
	outFile.close();

}

void SongList::addInput(Song &mySong)
{
	char titleInput[MAX], artistInput[MAX], albumInput[MAX];
	char userChoice;
	int minInput = 0, secInput = 0;
	
	cout << "Please add song to be added to the library" << endl;
	cout << "Title: ";
	cin.getline(titleInput, MAX, '\n');
	cout << "Artist: ";
	cin.getline(artistInput, MAX, '\n');
	cout << "Duration minutes (space) seconds: ";
	cin >> minInput;
	if(!cin)
	{
		while(!cin)
		{
			cout << "Bad input. Add integers only" << endl;
			cin.clear();
			cin.ignore(10, '\n');
	
			cout << "Duration minutes (space) seconds: ";
			cin >> minInput;
		}
	}
	cin.ignore();
	cin >> secInput;
	if(!cin)
	{
		while(!cin)
		{
			cout << "Bad input. Add integers only" << endl;
			cin.clear();
			cin.ignore(10, '\n');
	
			cout << "Duration minutes (space) seconds: ";
			cin >> secInput;
		}
	}
	cin.clear();
	cin.ignore(10, '\n');
	cout << "Album: ";
	cin.getline(albumInput, MAX, '\n');

	//echo information for validation.
	cout << "**********************" << endl;
	cout << "You entered: " << endl;
	cout << "Title: " << titleInput << endl;
	cout << "Artist: " << artistInput << endl;
	cout << "Duration: " << minInput << ":" << secInput << endl;
	cout << "Album: " << albumInput << endl << endl;
	cout << "**********************" << endl;

	do
	{
		cout << "Do you want to add song as displayed? (y or n): ";
		cin >> userChoice;
		cin.ignore(10, '\n');
		cin.clear();
	
		if ((tolower(userChoice) == 'y'))
		{
			cout << "**********************" << endl;
			cout << "Adding song to the library!" << endl;
			cout << "**********************" << endl;

			mySong.setTitle(titleInput);
			mySong.setArtist(artistInput);
			mySong.setMin(minInput);
			mySong.setSec(secInput);
			mySong.setAlbum(albumInput);

			addSong(mySong);
		}
				
		else if ((tolower(userChoice) == 'n'))
		{
			cout << "**********************" << endl;
			cout << "Discarding information" << endl;
			cout << "**********************" << endl;
		}
	}
	while ((tolower(userChoice) != 'y') && (tolower(userChoice) != 'n'));
}
