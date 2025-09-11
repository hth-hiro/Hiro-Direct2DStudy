#include "Project_Direct2D.h"
#include "DemoGameApp.h"

void RedirectIOToConsole()
{
    AllocConsole(); // �ܼ� â ����

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout); // ǥ�� ��� ���𷺼�
    freopen_s(&fp, "CONOUT$", "w", stderr); // ǥ�� ���� ���𷺼�
    freopen_s(&fp, "CONIN$", "r", stdin);   // ǥ�� �Է� ���𷺼�

    std::ios::sync_with_stdio(); // C++ ����� ����ȭ
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    RedirectIOToConsole();

    DemoGameApp App;

    App.Initialize();
    App.Run();
    App.Uninitialize();

    FreeConsole();

    return 0;
}