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
