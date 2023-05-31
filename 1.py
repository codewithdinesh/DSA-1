class Record:
    def __init__(self):
        self.name = None
        self.num = None

    def setName(self, name):
        self.name = name

    def setNumber(self, num):
        self.num = num

    def getName(self):
        return self.name

    def getNumber(self):
        return self.num

    def __str__(self):
        print("\nName: "+str(self.name)+"\nNumber: "+str(self.num))


class Hashtable:
    def __init__(self):
        self.size = int(input("\nEnter Size of Hashtable: "))
        self.table = list(None for i in range(self.size))
        self.elementCount = 0
        self.camparisonsCount = 0

    def Hash(self, record):
        return record % self.size

    def isFull(self):
        if(self.elementCount == self.size):
            return True
        else:
            return False

    def insert(self, record):
        # check overflow or not
        if self.isFull():
            print("\nHashtable is Full , Overflow...")
            return False

        isStored = False
        # get hash position
        position = self.Hash(record.num)

        if self.table[position] == None:
            self.table[position] = record
            isStored = True

            print("Stored Record for Name: "+str(record.name) +
                  "\nNumber : "+str(record.num)+" Stored at "+str(position))
            self.elementCount += 1
        # if Collision
        else:
            print("Print Collision Occured For Element ", str(record.name))
            position += 1

            while self.table[position] is not None:
                position += 1
                if(position > self.size):
                    position = 0

            self.table[position] = record
            print("Stored Record for Name: "+str(record.name) +
                  "\nNumber : "+str(record.num)+" Stored at "+str(position))
            isStored = True
            self.elementCount += 1
        return isStored

    def search(self, record):
        position = self.Hash(record.num)
        found = False

        if self.table[position] != None:
            if(self.table[position].getName() == record.name and self.table[position].getNumber() == record.num):
                found = True
                print("Phone number found at position {} ".format(
                    position))
                return position
            else:
                position += 1
                if(position > self.size):
                    position = 0

                while self.table[position] != None:
                    if(self.table[position].getName() == record.name and self.table[position].getNumber() == record.num):
                        found = True
                        print("Phone number found at position {} ".format(
                            position))
                        return position
                    position+=1 