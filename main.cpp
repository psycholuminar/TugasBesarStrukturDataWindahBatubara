#include "header.h"

int main() {
    dllFirma FirmaList;
    dllKasus KasusList;
    StackOperation undoStack, redoStack;

    createDllFirma(FirmaList);
    createDllKasus(KasusList);
    createStack(undoStack);
    createStack(redoStack);

    // Sample Kasus
    string KasusName1 = "Pembunuhan Rafif Radithya oleh Indra";
    string KasusName2 = "Pemalsuan Identitas oleh Fauzan";
    string KasusName3 = "Pembunuhan di Bojong Soang";

    insertLastKasus(KasusList, 101, KasusName1);
    insertLastKasus(KasusList, 102, KasusName2);
    insertLastKasus(KasusList, 103, KasusName3);

    bool running = true;
    int cekInput;

    while (running) {
        displayMenu();
        cin >> cekInput;

        if (cekInput == 1) {
            int KasusId;
            cout << "Masukkan ID Kasus yang Ingin di Tambahkan ke Cursor: ";
            cin >> KasusId;
            addKasusUsingCursor(FirmaList, KasusList, KasusId);
        }
        else if (cekInput == 2) {
            int FirmaId;
            string FirmaName;
            cout << "Masukkan ID Firma: ";
            cin >> FirmaId;
            cout << "Masukkan Nama Firma: ";
            cin >> FirmaName;
            insertLastFirma(FirmaList, FirmaId, FirmaName);

            Operation op;
            op.type = "insert";
            op.FirmaId = FirmaId;
            op.FirmaName = FirmaName;
            op.KasusCount = 0;
            for (int i = 0; i < MAX_Kasus; i++) {
                op.Kasus[i] = 0;
            }

            push(undoStack, op);
            while (!isEmpty(redoStack)) {
                pop(redoStack);
            }

            cout << "Firma berhasil di Tambah." << endl;
        }
        else if (cekInput == 3) {
            if (FirmaList.cursor) {
                Operation op;
                op.type = "delete";
                op.FirmaId = FirmaList.cursor->id;
                op.FirmaName = FirmaList.cursor->name;
                op.KasusCount = FirmaList.cursor->KasusCount;

                for (int i = 0; i < FirmaList.cursor->KasusCount; i++) {
                    op.Kasus[i] = FirmaList.cursor->Kasus[i];
                }

                deleteFirma(FirmaList, FirmaList.cursor);
                push(undoStack, op);
                while (!isEmpty(redoStack)) {
                    pop(redoStack);
                }

                cout << "Firma Berhasil di Hapus" << endl;
            } else {
                cout << "Tidak ada Firma yang Dipilih Cursor" << endl;
            }
        }
        else if (cekInput == 4) {
            undo(FirmaList, undoStack, redoStack);
        }
        else if (cekInput == 5) {
            redo(FirmaList, undoStack, redoStack);
        }
        else if (cekInput == 6) {
            display(FirmaList, KasusList);
        }
        else if (cekInput == 7) {
            displayKasus(KasusList);
        }
        else if (cekInput == 8) {
            moveCursorRight(FirmaList);
        }
        else if (cekInput == 9) {
            moveCursorLeft(FirmaList);
        }
        else if (cekInput == 10) {
            int KasusId;
            cout << "Masukkan ID Kasus yang ingin Dihapus: ";
            cin >> KasusId;
            deleteKasus(KasusList, KasusId);
        }
        else if (cekInput == 11) {
            int KasusId;
            cout << "Masukkan ID Kasus yang ingin Dihapus dari Firma Cursor: ";
            cin >> KasusId;
            removeKasusFromCursor(FirmaList, KasusId);
        }
        else if (cekInput == 12) {
            int KasusId;
            string KasusName;
            cout << "Masukan ID Kasus (3 Angka Unik): ";
            cin >> KasusId;
            cout << "Masukkan Nama Kasus: ";
            cin.ignore();
            getline(cin, KasusName);
            insertLastKasus(KasusList, KasusId, KasusName);
            cout << "Kasus Berhasil Ditambah." << endl;
        }
        else if (cekInput == 13) {
            running = false;
            cout << "EXIT" << endl;
        }
        else {
            cout << "Masukkan Input yang Tersedia." << endl;
        }
    }
    return 0;
}
