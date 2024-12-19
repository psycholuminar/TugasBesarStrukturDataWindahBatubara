#include "header.h"

void createStack(StackOperation &s) {
    s.top = -1;
}

bool isEmpty(StackOperation &s) {
    return s.top == -1;
}

bool isFull(StackOperation &s) {
    return s.top == MAX_STACK - 1;
}

void push(StackOperation &s, Operation &op) {
    if (!isFull(s)) {
        s.top++;
        s.items[s.top] = op;
    }
}

Operation pop(StackOperation &s) {
    Operation op;
    if (!isEmpty(s)) {
        op = s.items[s.top];
        s.top--;
        return op;
    }
    return op;
}

Operation getTop(StackOperation &s) {
    if (!isEmpty(s)) {
        return s.items[s.top];
    }
    Operation emptyOp;
    return emptyOp;
}

void createDllFirma(dllFirma &dllF) {
    dllF.head = nullptr;
    dllF.tail = nullptr;
    dllF.cursor = nullptr;
}

void createDllKasus(dllKasus &dllC) {
    dllC.head = nullptr;
}

void insertLastFirma(dllFirma &dllF, int id, string &name) {
    adrFirma newFirma = new Firma;
    newFirma->id = id;
    newFirma->name = name;
    newFirma->KasusCount = 0;
    newFirma->prev = nullptr;
    newFirma->next = nullptr;

    if (!dllF.head) {
        dllF.head = dllF.tail = dllF.cursor = newFirma;
    } else {
        dllF.tail->next = newFirma;
        newFirma->prev = dllF.tail;
        dllF.tail = newFirma;
    }
}

void deleteFirma(dllFirma &dllF, adrFirma Firma) {
    if (!Firma) return;

    if (Firma == dllF.cursor) {
        if (Firma->next) {
            dllF.cursor = Firma->next;
        } else if (Firma->prev) {
            dllF.cursor = Firma->prev;
        }
    }

    if (Firma->prev) {
        Firma->prev->next = Firma->next;
    } else {
        dllF.head = Firma->next;
    }

    if (Firma->next) {
        Firma->next->prev = Firma->prev;
    } else {
        dllF.tail = Firma->prev;
    }

    delete Firma;
}

void insertLastKasus(dllKasus &dllC, int id, string &name) {
    adrKasus newKasus = new Kasus;
    newKasus->id = id;
    newKasus->name = name;
    newKasus->next = nullptr;

    if (!dllC.head) {
        dllC.head = newKasus;
    } else {
        adrKasus temp = dllC.head;
        while (temp->next) temp = temp->next;
        temp->next = newKasus;
    }
}

void moveCursorRight(dllFirma &dllF) {
    if (dllF.cursor && dllF.cursor->next) {
        dllF.cursor = dllF.cursor->next;
        cout << "Cursor dipindahkan ke: " << dllF.cursor->name << endl;
    } else {
        cout << "Tidak ada Firma berikutnya" << endl;
    }
}

void moveCursorLeft(dllFirma &dllF) {
    if (dllF.cursor && dllF.cursor->prev) {
        dllF.cursor = dllF.cursor->prev;
        cout << "Cursor dipindahkan ke: " << dllF.cursor->name << endl;
    } else {
        cout << "Tidak ada Firma sebelumnya" << endl;
    }
}

void display(dllFirma &dllF, dllKasus &dllC) {
    adrFirma temp = dllF.head;
    while (temp) {
        cout << "ID: " << temp->id << ", Nama: " << temp->name;
        if (temp == dllF.cursor) {
            cout << " (Cursor)";
        }
        cout << "\nKasus Terdaftar: ";
        for (int i = 0; i < temp->KasusCount; i++) {
            cout << getKasusName(dllC, temp->Kasus[i]) << " (ID: " << temp->Kasus[i] << ") ";
        }
        cout << endl << endl;
        temp = temp->next;
    }
}

void displayKasus(dllKasus &dllC) {
    adrKasus temp = dllC.head;
    cout << "Daftar Kasus:\n";
    while (temp) {
        cout << "ID: " << temp->id << ", Nama: " << temp->name << endl;
        temp = temp->next;
    }
    cout << endl;
}

bool searchKasus(dllKasus &dllC, int KasusId) {
    adrKasus temp = dllC.head;
    while (temp) {
        if (temp->id == KasusId) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

string getKasusName(dllKasus &dllC, int KasusId) {
    adrKasus temp = dllC.head;
    while (temp) {
        if (temp->id == KasusId) {
            return temp->name;
        }
        temp = temp->next;
    }
    return "Kasus Tidak Dikenal";
}

bool addKasusUsingCursor(dllFirma &dllF, dllKasus &dllC, int KasusId) {
    if (!dllF.cursor) {
        cout << "Tidak ada Firma yang dipilih (cursor null)" << endl;
        return false;
    }

    if (!searchKasus(dllC, KasusId)) {
        cout << "ID Kasus " << KasusId << " tidak ditemukan" << endl;
        return false;
    }

    for (int i = 0; i < dllF.cursor->KasusCount; i++) {
        if (dllF.cursor->Kasus[i] == KasusId) {
            cout << "Firma sudah terdaftar dalam kasus ini" << endl;
            return false;
        }
    }

    if (dllF.cursor->KasusCount == MAX_Kasus) {
        cout << "Firma sudah mencapai batas maksimum kasus" << endl;
        return false;
    }

    dllF.cursor->Kasus[dllF.cursor->KasusCount++] = KasusId;
    cout << "Kasus " << getKasusName(dllC, KasusId) << " (ID: " << KasusId << ") ditambahkan ke Firma " << dllF.cursor->name << endl;
    return true;
}

void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Tambah Kasus ke Firma yang ditunjuk Cursor\n";
    cout << "2. Tambah Firma\n";
    cout << "3. Hapus Firma yang ditunjuk Cursor\n";
    cout << "4. Undo Operasi pada Firma (Insert/Hapus)\n";
    cout << "5. Redo Operasi pada Firma (Insert/Hapus)\n";
    cout << "6. Display Firma\n";
    cout << "7. Display Kasus\n";
    cout << "8. Pindah Kursor ke Bawah\n";
    cout << "9. Pindah Kursor ke Atas\n";
    cout << "10. Hapus Salah Satu Kasus\n";
    cout << "11. Hapus Kasus dari Firma yang Ditunjuk\n";
    cout << "12. Tambah Kasus\n";
    cout << "13. Exit\n";
    cout << "Masukkan input yang ingin dilakukan: ";
}

void undo(dllFirma &dllF, StackOperation &undoStack, StackOperation &redoStack) {
    if (isEmpty(undoStack)) {
        cout << "Tidak ada yang bisa di Undo" << endl;
        return;
    }

    Operation op = pop(undoStack);

    if (op.type == "insert") {
        adrFirma temp = dllF.head;
        while (temp && temp->id != op.FirmaId) {
            temp = temp->next;
        }
        if (temp) {
            Operation redoOp;
            redoOp.type = "insert";
            redoOp.FirmaId = temp->id;
            redoOp.FirmaName = temp->name;
            redoOp.KasusCount = temp->KasusCount;
            for (int i = 0; i < temp->KasusCount; i++) {
                redoOp.Kasus[i] = temp->Kasus[i];
            }
            deleteFirma(dllF, temp);
            push(redoStack, redoOp);
        }
    } else if (op.type == "delete") {
        insertLastFirma(dllF, op.FirmaId, op.FirmaName);
        if (dllF.tail) {
            Operation redoOp;
            redoOp.type = "delete";
            redoOp.FirmaId = op.FirmaId;
            redoOp.FirmaName = op.FirmaName;
            redoOp.KasusCount = op.KasusCount;
            for (int i = 0; i < op.KasusCount; i++) {
                redoOp.Kasus[i] = op.Kasus[i];
            }
            dllF.tail->KasusCount = op.KasusCount;
            for (int i = 0; i < op.KasusCount; i++) {
                dllF.tail->Kasus[i] = op.Kasus[i];
            }
            push(redoStack, redoOp);
        }
    }
}

void redo(dllFirma &dllF, StackOperation &undoStack, StackOperation &redoStack) {
    if (isEmpty(redoStack)) {
        cout << "Tidak ada yang bisa di Redo" << endl;
        return;
    }

    Operation op = pop(redoStack);

    if (op.type == "insert") {
        insertLastFirma(dllF, op.FirmaId, op.FirmaName);
        if (dllF.tail) {
            Operation undoOp;
            undoOp.type = "insert";
            undoOp.FirmaId = op.FirmaId;
            undoOp.FirmaName = op.FirmaName;
            undoOp.KasusCount = op.KasusCount;
            for (int i = 0; i < op.KasusCount; i++) {
                undoOp.Kasus[i] = op.Kasus[i];
            }
            dllF.tail->KasusCount = op.KasusCount;
            for (int i = 0; i < op.KasusCount; i++) {
                dllF.tail->Kasus[i] = op.Kasus[i];
            }
            push(undoStack, undoOp);
        }
    } else if (op.type == "delete") {
        adrFirma temp = dllF.head;
        while (temp && temp->id != op.FirmaId) {
            temp = temp->next;
        }
        if (temp) {
            Operation undoOp;
            undoOp.type = "delete";
            undoOp.FirmaId = op.FirmaId;
            undoOp.FirmaName = op.FirmaName;
            undoOp.KasusCount = op.KasusCount;
            for (int i = 0; i < op.KasusCount; i++) {
                undoOp.Kasus[i] = op.Kasus[i];
            }
            deleteFirma(dllF, temp);
            push(undoStack, undoOp);
        }
    }
}

void deleteKasus(dllKasus &dllC, int KasusId) {
    if (!dllC.head) return;

    adrKasus temp = dllC.head;
    adrKasus prev = nullptr;

    while (temp && temp->id != KasusId) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        cout << "Kasus ID " << KasusId << " Tidak Ditemukan." << endl;
        return;
    }

    if (prev) {
        prev->next = temp->next;
    } else {
        dllC.head = temp->next;
    }

    delete temp;
    cout << "Kasus ID " << KasusId << " Berhasil Dihapus." << endl;
}

void removeKasusFromCursor(dllFirma &dllF, int KasusId) {
    if (!dllF.cursor) {
        cout << "Cursor NULL / Tambahkan Firma." << endl;
        return;
    }

    bool found = false;
    for (int i = 0; i < dllF.cursor->KasusCount; i++) {
        if (dllF.cursor->Kasus[i] == KasusId) {
            found = true;
            for (int j = i; j < dllF.cursor->KasusCount - 1; j++) {
                dllF.cursor->Kasus[j] = dllF.cursor->Kasus[j + 1];
            }
            dllF.cursor->KasusCount--;
            break;
        }
    }

    if (found) {
        cout << "Kasus ID " << KasusId << " Dihapus dari Firma " << dllF.cursor->name << " Berhasil." << endl;
    } else {
        cout << "Kasus ID " << KasusId << " Tidak di Handle oleh Firma." << endl;
    }
}
