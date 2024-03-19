
#include <QCoreApplication>
#include <windows.h>
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QDateTime>
#include <QTime>
#include <QDate>
#include <QTextStream>


// Forward declaration of WndProc
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const wchar_t CLASS_NAME[] = L"ClipboardListenerWindowClass";

    // Get an instance handle for the application
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    // Describe the window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    // Register the window class
    RegisterClass(&wc);

    // Create a hidden window
    HWND hWnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class name
        L"Clipboard Listener Window",    // Window title (not relevant for hidden window)
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // Position and size
        nullptr,                        // Parent window
        nullptr,                        // Menu
        hInstance,                      // Instance handle
        nullptr                         // Additional application data
        );

    if (hWnd == nullptr) {
        std::cerr << "Failed to create window\n";
        return 1;
    }

    // Register the window to receive clipboard update notifications
    AddClipboardFormatListener(hWnd);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Cleanup: Unregister the window from receiving clipboard updates
    RemoveClipboardFormatListener(hWnd);
    DestroyWindow(hWnd);

    return a.exec();
}

// Window procedure to handle messages
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CLIPBOARDUPDATE: {
        // Clipboard content has changed
        std::cout << "Clipboard content has changed." << std::endl;

        QString filename = "timestamp.txt"; //creaing a file name
        //not including a directory
        //just the file name and extension
        //will put in the current application directory

        QFile file(filename);
        //constructor of the file takes the name of the file

        QTextStream out(&file);

        if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) //just need to set this flag
        {

            QString now = QDateTime::currentDateTime().time().toString();

            out << now << Qt::endl;
        }
        else {
            qInfo() << file.errorString(); //returns error in a string representation
        }
    }

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

