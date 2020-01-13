#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char Byte;

typedef struct Client
{
	char Id[9];
	char Phone[12];
} Client;

typedef struct ShortClient
{
	Byte ShortId[4];
	Byte ShortPhone[5];
} ShortClient;

Client GetClient()
{
	printf("Please enter client id followed by client phone: ");
	Client result;
	scanf("%s%s", result.Id, result.Phone);
	return result;
}

int CharToInt(char ch)
{
	return ch - '0';
}

void Encode(char* string, Byte* output)
{
	int stringSize = strlen(string);

	for (int i = 0; i < stringSize; ++i)
	{
		int byteIndex = i / 2;
		if (i % 2 == 0)
		{
			output[byteIndex] = CharToInt(string[i]);
		}
		else
		{
			output[byteIndex] |= (CharToInt(string[i]) << 4);
		}
	}
}

void EncodePhone(char* phone, Byte* output)
{
	for (int i = 3; i < strlen(phone) - 1; ++i)
	{
		phone[i] = phone[i + 1];
	}
	Encode(phone, output);
}

ShortClient EncodeClient(Client client)
{
	ShortClient result;
	Encode(client.Id, result.ShortId);
	EncodePhone(client.Phone, result.ShortPhone);
	return result;
}

ShortClient* CreateShortClientArray(int count)
{
	ShortClient* result = malloc(sizeof(ShortClient) * count);

	for (int i = 0; i < count; ++i)
	{
		result[i] = EncodeClient(GetClient());
	}

	return result;
}

char* DecodePhone(Byte encodedPhone[5])
{
	char* result = malloc(sizeof(char) * 12);

	for (int i = 0; i < 5; ++i)
	{
		result[i * 2] = (encodedPhone[i] & 15) + '0';
		result[(i * 2) + 1] = ((encodedPhone[i] >> 4) & 15) + '0';
	}

	for (int i = 11 - 1; i >= 4; i--)
	{
		result[i] = result[i - 1];
	}

	result[3] = '-';
	result[11] = '\0';
	return result;
}

int IsByteArrayEqual(Byte arr1[4], Byte arr2[4])
{
	for (int i = 0; i < 4; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			return 0;
		}
	}
	return 1;
}

char* SearchClientByID(ShortClient* shortClientArray, int arraySize, char idToFind[9])
{
	Byte shortId[4];
	Encode(idToFind, shortId);

	for (int i = 0; i < arraySize; ++i)
	{
		if (IsByteArrayEqual(shortId,shortClientArray[i].ShortId))
		{
		    return DecodePhone(shortClientArray[i].ShortPhone);
		}
	}

	return NULL;
}

void main()
{
	int n;
	ShortClient* arr;
	char id[9];
	char* phone = NULL;

	printf("Please enter the number of clients: ");
	scanf("%d", &n);
	arr = CreateShortClientArray(n);
	scanf("%s", id);
	phone = SearchClientByID(arr, n, id);
	if (phone == NULL)

		printf("Can not find client with i.d. %s\n", id);
	else
	{

		printf("The phone number of client i.d. %s is %s\n", id, phone);

		free(phone);

	}
	free(arr);
}
