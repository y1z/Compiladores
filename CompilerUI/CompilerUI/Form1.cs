using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;
// 
using System.Reflection;
using System.Resources;
using System.Diagnostics;
using System.Management;

namespace CompilerUI
{
  public partial class CompilerWindow : Form
  {
    /*---------------------------Constructors---------------------------*/
    public CompilerWindow()
    {
      InitializeComponent();
      isDllLoaded = false;

      // find out if the assembly is 64x or 86x 
      if (IntPtr.Size == 4)
      {
        isCurrentAssemblyIsX64 = false;
      }
      else
      {
        isCurrentAssemblyIsX64 = true;
      }
      IsComplied = false;

      // Gos to the Assembly and Searches every attribute untli it finds a DebuggableAttribute Or Not.
      isCurrentAssemblyIsDebug = Assembly.GetEntryAssembly().GetCustomAttributes(false).OfType<DebuggableAttribute>().Any(da => da.IsJITTrackingEnabled);
    }
    /*--------------------------Variables-----------------------------*/
    String DllFullPath;
    // this will hold the file path 
    string m_SaveFilePath = @"";
    // this will let us know if we already have a file path 
    bool isSaveFileSet = false;

    dynamic ComplierDllInstance;

    bool isDllLoaded;
    bool isCurrentAssemblyIsDebug;
    bool isCurrentAssemblyIsX64;
    bool IsComplied;
    /*---------------------------Functions---------------------------*/

    private String GetCorrectDllName()
    {
      String Result = "Compiler";

      // check if we are in debug mode 
      if (isCurrentAssemblyIsDebug)
      {
        Result += "D";
      }
      else
      {
        Result += "R";
      }

      // check platform
      if (isCurrentAssemblyIsX64)
      {
        Result += "x64";
      }
      else
      {
        Result += "x86";
      }

      Result += ".dll";

      return Result;
    }// end function

    private void Form1_Load(object sender, EventArgs e)
    {
      if (!LoadCompilerDll())
      {
        MessageBox.Show("Did not load Dll");
        return;
      }

    }// end function 
    /// <summary>
    ///  checks if the dll if loaded correctly
    /// </summary>
    /// <returns></returns>
    private bool LoadCompilerDll()
    {
      // use this variable to navigate
      String ProcessFullPath = Process.GetCurrentProcess().MainModule.FileName;

      DirectoryInfo Up1 = Directory.GetParent(ProcessFullPath);
      DllFullPath = Up1.FullName;

      // Move to outside of the project folder.
      for (int i = 0; i < 5; ++i)
      {
        Up1 = Directory.GetParent(DllFullPath);
        DllFullPath = Up1.FullName;
      }

      // works if there in  the same folder 
      DllFullPath += "\\Compiler";

      // go the relevant Platform
      if (isCurrentAssemblyIsX64)
      {
        DllFullPath += "\\x64";
      }
      else
      {
        DllFullPath += "\\x86";
      }
      // the 2 Platform are contain in a Exe
      DllFullPath += "\\Exe";

      if (isCurrentAssemblyIsDebug)
      {
        DllFullPath += "\\Debug\\";
      }
      else
      {
        DllFullPath += "\\Release\\";
      }

      DllFullPath += GetCorrectDllName();
      /*Logar hacer esto*/
      // DllFullPath = BaseProj + \\Compiler\\Platform\\Configeration\\dllFileName;

      var Dll = Assembly.UnsafeLoadFrom(DllFullPath);

      // Note both name "Complier" and "Manager" have to be upper case 
      // because of how i named them 
      var DllType = Dll.GetType("Compiler.Manager");

      ComplierDllInstance = Activator.CreateInstance(DllType);

      // what the fuck is this black magic 
      isDllLoaded = ComplierDllInstance != null;

      if (isDllLoaded == false)
      {
        MessageBox.Show("No se pudo Cargar la dll", "", MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
      else
      {
        MessageBox.Show("(Success)Se pudo cargar la dll " + DllFullPath, "Everthing is alright");
      }

      return isDllLoaded;
    }// Function end 

    /// <summary>
    ///  Compile Program
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void compilarToolStripMenuItem1_Click(object sender, EventArgs e)
    {
      // For when the dll is loaded
      if (isDllLoaded)
      {
        // the null termination character (aka '\0') is just for safety
        String[] Output = ComplierDllInstance.compileProgram(MainTextBox.Text + '\0');

        // This trasfer the Parsed text to the output Text box (The black one)
      
        DataParser dataParser = new DataParser();
        
        dataParser.ParseCompilerData(Output, ref m_TokenDataView, ref OutputTextBox,IsComplied);

        IsComplied = true;
      }
      else
      {
        MessageBox.Show("No se pudo Cargar la dll ", "Everything failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
      }

    }// function end 

    /// <summary>
    /// (Abrir) Open Text file 
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void abrirToolStripMenuItem_Click(object sender, EventArgs e)
    {
      OpenFileDialog File = new OpenFileDialog();
      File.Filter = "Text Files |*.txt";
      if (File.ShowDialog() == DialogResult.OK)
      {
        MainTextBox.Clear();
        StreamReader Reader = new StreamReader(File.OpenFile());
        MainTextBox.Text = Reader.ReadToEnd();
      }
      else
      {
        MessageBox.Show("Error Opening file ", "unknown Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
      }

    }// function end 

    /// <summary>
    /// (Guardar Como) Here we save the text file 
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void gradarComoToolStripMenuItem_Click(object sender, EventArgs e)
    {
      SaveFileDialog SaveFile = new SaveFileDialog();
      SaveFile.Filter = "Text Files | *.txt";
      SaveFile.DefaultExt = "txt";
      // open the dialog 
      if (SaveFile.ShowDialog() == DialogResult.OK)
      {
        StreamWriter stream = new StreamWriter(SaveFile.FileName);
        stream.Write(MainTextBox.Text);
        // so the user doesn't see the Save file Dialog all the time 
        if (isSaveFileSet == false)
        {
          isSaveFileSet = true;
        }
        // Change file every time the user change files 
        m_SaveFilePath = SaveFile.FileName;
        stream.Close();
      }

    }// function end
    /// <summary>
    /// (Guardar) just the regular save option
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void gradarToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (isSaveFileSet == false)
      {
        //call Gradar Como Method
        gradarComoToolStripMenuItem_Click(sender, e);
      }
      else
      {
        StreamWriter stream = new StreamWriter(m_SaveFilePath);
        stream.Write(MainTextBox.Text);
        stream.Close();
      }
    }// end function
    /// <summary>
    /// (Sailr) Quits the application
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    public void salirToolStripMenuItem1_Click(object sender, EventArgs e)
    {
      MessageBox.Show("Love is fake, pain is real: adios fucker no one cared about, BAKA");
      Application.Exit();
    }// end function

    private void textBox2_TextChanged(object sender, EventArgs e)
    {

    }

    private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
    {

    }


    private void MainTextBox_TextChanged(object sender, EventArgs e)
    {

    }
    /// <summary>
    /// (Nuevo) Here is where ask the user if they what 
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void nuevoToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (isSaveFileSet)
      {
        var result = MessageBox.Show("Quieres Guardar lo que hiceste?", "Message Box", MessageBoxButtons.YesNoCancel);

        if (result == DialogResult.Yes)
        {
          // Esto Guarda en un archivo
          gradarToolStripMenuItem_Click(sender, e);

          MainTextBox.Text = "";
          isSaveFileSet = false;
          m_SaveFilePath = "";
        }
        else if (result == DialogResult.No)
        {
          MainTextBox.Text = "";
          isSaveFileSet = false;
          m_SaveFilePath = "";
        }
        else if (result == DialogResult.Cancel)
        {
          return;
        }

        MainTextBox.Text = "";
      }
      else// save a new file
      {
        gradarToolStripMenuItem_Click(sender, e);
      }
    }// end function

  }

}
