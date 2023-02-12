using System;
using Autodesk.AutoCAD.Runtime;
using System.Windows.Forms;

namespace MyAutoCADDll
{
    public class Commands : IExtensionApplication
    {
        // эта функция будет вызываться при выполнении в AutoCAD команды "TestCommand"
        [CommandMethod("TestCommand")]
        public void MyCommand()
        {
            MessageBox.Show("Привет, Арина.");
        }

        // Функции Initialize() и Terminate() необходимы, чтобы реализовать интерфейс IExtensionApplication
        public void Initialize()
        {
            MessageBox.Show("Plugin has been initialized!");
        }

        public void Terminate()
        {
            MessageBox.Show("Plugin has been terminated!");
        }
    }
}