bool arrayEquals(bool a1[], bool a2[], int len) {
	for (int i = 0; i < len; i++) {
		if (a1[i] != a2[i]) {
			return false;
		}
	}
	return true;
}

void arraySubset(bool arr[], int startIndex, int newLength, bool newArr[]) {
	newArr[newLength] = { 0 };
	for (int i = 0; i < newLength; i++) {
		newArr[i] = arr[startIndex + i];
	}
	return;
}

void arraySubset(int arr[], int startIndex, int newLength, int newArr[]) {
	newArr[newLength] = { 0 };
	for (int i = 0; i < newLength; i++) {
		newArr[i] = arr[startIndex + i];
	}
	return;
}

void setArray(bool arr[], bool newArr[], int len) {
	for (int i = 0; i < len; i++) {
		arr[i] = newArr[i];
	}
}

void setArray(double arr[], double newArr[], int len) {
	for (int i = 0; i < len; i++) {
		arr[i] = newArr[i];
	}
}

void notArray(bool arr[], int len) {
	for (int i = 0; i < len; i++) {
		arr[i] = !arr[i];
	}
}

int arr2bin4(bool arr[]) {
	int a = arr[0];
	int b = arr[1];
	int c = arr[2];
	int d = arr[3];

	return 1 * a + 2 * b + 4 * c + 8 * d;
}

int arr2bin2(bool arr[]) {
	int x = 1 * arr[0] + 2 * arr[1];
	return x;
}