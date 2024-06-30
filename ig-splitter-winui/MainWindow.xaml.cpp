#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif


#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.h>
#include <iostream>
#include <shobjidl_core.h>

#include "ImageProcessor.h"


using namespace winrt;
using namespace Microsoft::UI::Xaml;



// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::ig_splitter_winui::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        OpenFilePickerAsync();
    }

    Windows::Foundation::IAsyncAction MainWindow::OpenFilePickerAsync()
    {
        HWND hwnd = GetActiveWindow();
        // Creazione del file picker
        Windows::Storage::Pickers::FileOpenPicker picker;
        picker.as<IInitializeWithWindow>()->Initialize(hwnd);

        picker.ViewMode(Windows::Storage::Pickers::PickerViewMode::Thumbnail);
        picker.SuggestedStartLocation(Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
        picker.FileTypeFilter().Append(L".png");
        picker.FileTypeFilter().Append(L".jpg");

        // Utilizzo di co_await per attendere la selezione del file
        Windows::Storage::StorageFile file = co_await picker.PickSingleFileAsync();
        if (file != nullptr)
        {
            hstring fileName = file.Name();
            OutputDebugString((L"File selected: " + fileName + L"\n").c_str());
            ImageProcessor ip;
            ip.SplitImage();
        }
    }
}
