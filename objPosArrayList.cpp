#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize >= arrayCapacity) { //if array is full
        return;
    }
    for (int i = listSize; i > 0; i--) {
        aList[i] = aList[i - 1];
    }
    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize >= arrayCapacity) {
        return; // Do nothing if the array is full
    }
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if (listSize == 0) {
        return; // Do nothing if the array is empty
    }
    for (int i = 0; i < listSize - 1; i++) {
        aList[i] = aList[i + 1];
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    if (listSize == 0) {
        return; 
    }
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return (listSize > 0) ? aList[0] : objPos(); // Return default objPos if empty
}

objPos objPosArrayList::getTailElement() const
{
    return (listSize > 0) ? aList[listSize - 1] : objPos(); // Return default objPos if empty
}

objPos objPosArrayList::getElement(int index) const
{
    if (index >= 0 && index < listSize) {
        return aList[index];
    }
    return objPos(); // Return default objPos for invalid index
}