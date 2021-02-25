class matkul:

    # Inisialisasi
    def __init__(self, name):
        self.count = 0
        self.name = name
        self.prereq = []
    
    # Menambah prereq
    def addPrereq(self, name):
        self.count += 1
        self.prereq.append(name)

    # Mencari dan membuang prereq
    def removePrereq(self, name):
        for word in self.prereq:
            if (word == name):
                word = ""
                self.count -= 1

    # Menandakan matkul sudah diambil
    def take(self):
        self.count -= 1

def createList(nama_file):
    list_matkul = []
    file = open(nama_file + ".txt", "r")
    for line in file:
        line = line.rstrip(".\n").split(", ")
        newmat = matkul(str(line[0]))

        for i in range (len(line)):
            if (i > 0):
                newmat.addPrereq(str(line[i]))

    list_matkul.append(newmat)
    return list_matkul


def isAll(list_matkul):
    for matkul in list_matkul:
        if (matkul.count > 0):
            return False
    return True

nama_file = "tc1"
list_matkul = createList(nama_file)


for matkul in list_matkul:
    print(matkul.name)
    print(matkul.count)
    print(matkul.prereq)
'''
i = 1
while not (isAll(list_matkul)):
    print("Semester ", i, ": ", end = "")
    for mata_kuliah in list_matkul:
        if (mata_kuliah.count == 0):
            mata_kuliah.take()
            for mk in list_matkul:
                mk.removePrereq(mata_kuliah.name)
    i+=1'''