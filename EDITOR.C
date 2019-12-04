#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void printTextEditor(char* ptr, int size);
void changeCursor(int size, int position);
void upperCase(char* ptr, int position);
void lowerCase(char* ptr, int position);
void printRes(char* ptr,int size);

int leftMove(int position);
int rightMove(int position, int size);
int backSpace(char* ptr, int size, int position);
int writeChar(char* ptr, int size, int position, char ch);

int main()
{
	char* textArr, text;
	int textSize, pos = 0;
	clrscr();

	//1.Get Text Size from User
	printf("Enter Text Size: ");
	scanf("%d", &textSize);

	//2.Dynamic Array
	textArr = (char*) malloc(textSize * sizeof(char));

	//3.Draw Text Area
	printTextEditor(textArr, textSize);

	//4.Start write on text Editor
	do
	{
		// Change Cursor position
		changeCursor(textSize, pos);

		text = getch();
		switch(text)
		{
			case NULL:
				text = getch();
				switch(text)
				{
					case 75: // left
						//go left
						pos = leftMove(pos);
						break;

					case 77: // Right
						pos = rightMove(pos, textSize);
						break;

					case 72:  // Upper
						upperCase(textArr, pos);
						break;

					case 80: // Lower
						lowerCase(textArr, pos);
						break;
				}
				break;

			case 8: //Backspace
				pos = backSpace(textArr, textSize, pos);
				break;

			case 13: //Enter
				printRes(textArr,textSize);
				break;

			default:
				pos = writeChar(textArr, textSize, pos, text);
				break;
		}
	}while(text != 27);


	free(textArr);
	return 0;
}

void printTextEditor(char* ptr, int size)
{
	int i;
	for(i=0; i<size; i++)
	{
		textattr(0x30);
		gotoxy(15+i, 10);
		ptr[i] = '\0';
		cprintf("%c", ptr[i]);
	}
}

void changeCursor(int size, int position)
{
	int i;
	for( i = 0; i< size; i++)
	{
		if(i == position)
			gotoxy(15+i,10);
	}
}

int leftMove(int position)
{
	position--;
	if(position<0)
	{
		position = 0;
	}
	return position;
}
int rightMove(int position, int size)
{
	position++;
	if(position > size)
	{
		position = size;
	}
	return position;
}

void upperCase(char* ptr, int position)
{
	if(ptr[position] >= 'a' && ptr[position] <= 'z')
	{
		ptr[position] -= 32;
	}
	printf("%c", ptr[position]);
}

void lowerCase(char* ptr, int position)
{
	if(ptr[position] >= 'A' && ptr[position] <= 'Z')
	{
		ptr[position] += 32;
	}
	printf("%c", ptr[position]);
}

int backSpace(char* ptr, int size, int position)
{
	int i;
	position--;
	if(position < 0 )
		position = 0;
	for( i = position; i < size; i++)
	{
		ptr[i] = ptr[i+1];
		gotoxy(15+i, 10);
		cprintf("%c", ptr[i]);
	}
	return position;
}

void printRes(char* ptr,int size)
{
	int i;
	textattr(0x07);
	clrscr();
	printf("You Printed Text is:\t [Esc to Exit].\n");
	for(i = 0; i< size; i++)
	{
		gotoxy(5+i, 5);
		printf("%c", ptr[i]);
	}
}

int writeChar(char* ptr, int size, int position, char ch)
{
	if(position >= 0 && position < size)
	{
		ptr[position] = ch;
		printf("%c", ptr[position]);
		position++;
	}

	if(position > size)
		position = size;

	return position;
}