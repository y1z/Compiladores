using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

/**
 * @brief this is where the parsing my own information from the compiler, i made because the 'CompilerWindow'
 * is becoming to big for me to handle ( ͡° ͜ʖ ͡°)
 * 
 */
namespace CompilerUI
{
  public partial class DataParser : Form
  {
    /*---------------------------Constructors---------------------------*/
    public DataParser()
    {
      m_ParseMode = ParseModes.ParamReading;
      m_OrderOfParse = new List<ParseModes>();
      m_ParamArgsCount = new List<int>();
    }// end constructor 

    /*--------------------------Variables-----------------------------*/

    enum ParseModes : int
    {
      UNKNOWN = -1,// unknown 
      ParamReading = 0,
      ErrorReading = 1,
      LexReading = 2,
      SytaxReading = 3,
      SemanticReading = 4
    };// end enum 

    List<ParseModes> m_OrderOfParse;
    //! this to determine are current mode for parsing 
    ParseModes m_ParseMode;
    //! this is where i store the information for each Parse-mode
    List<int> m_ParamArgsCount;
    //! help know which mode the use 
    String[] ModeIdentifiers = { "#ER_", "#LE_", "#SY_", "#SM_" };
    //! information that always at the beginning of the error messages
    const String m_ErrorInfo = "Compilation phase\tLine number\tDescription\t\t\tLine \r\n ---------------------------------------------------------------------------------------------------------------------------------------\r\n";

    //! to know which order to do the parse-sing
    /*---------------------------Functions---------------------------*/
    public bool ParseCompilerData(String[] CompilerData, ref DataGridViewRow GridView, ref DataGridView DataView, ref TextBox ErrorText,bool isAlreadyCompiled)
    {
      if (isAlreadyCompiled)
      {
        DataView.Rows.Clear();
      }


      ScanningForParams(CompilerData);

      ExacuteParams(CompilerData, ref GridView, ref DataView, ref ErrorText);
      return true;
    }// end function 

    private void ScanningForParams(String[] CompilerData)
    {
      String PossibleParam = "";
      // checking for the by adding everything until it hit the end, or a whitespace "#ER_", "#LE_", "#SY_", "#SM_"
      for (int i = 0; i < CompilerData[0].Length; ++i)
      {
        // checking in a reserved spot for the compiler 
        if (!CompilerData[0][i].Equals(' '))
        {
          PossibleParam += CompilerData[0][i];
        }
        if (PossibleParam.Length > 0 && CompilerData[0][i].Equals('_'))
        {
          int ParamCount = 0;
          //checking if the param exist 
          if (CheckingForParams(PossibleParam))
          {
            //trying to find out how many Error,LexTokens or other compiler thing to look for. 
            ParamCount = ScanNumbers(CompilerData[0], i, ref i);
            m_ParamArgsCount.Add(ParamCount);
          }

          PossibleParam = "";
        }

      }

      return;
    }// end function

    //! checks for the relevant string 
    private bool CheckingForParams(String PossibleMatch)
    {
      bool isMatchFound = false;

      for (int i = 0; i < ModeIdentifiers.Length; ++i)
      {
        //casting to equivalent parseMode
        if (PossibleMatch.Equals(ModeIdentifiers[i]))
        {
          isMatchFound = true;
          switch (i)
          {
            case (0):
              m_ParseMode = ParseModes.ErrorReading;
              m_OrderOfParse.Add(m_ParseMode);
              return isMatchFound;
            case (1):
              m_ParseMode = ParseModes.LexReading;
              m_OrderOfParse.Add(m_ParseMode);
              return isMatchFound;
            case (2):
              m_ParseMode = ParseModes.SytaxReading;
              m_OrderOfParse.Add(m_ParseMode);
              return isMatchFound;
            case (3):
              m_ParseMode = ParseModes.SemanticReading;
              m_OrderOfParse.Add(m_ParseMode);
              return isMatchFound;
          }

          isMatchFound = true;
        }

      }

      return isMatchFound;
    }// end function

    private int ScanNumbers(String Numbers, int Index, ref int Iteration)
    {
      // gets all the number necessary
      String JustNumber = "";

      int Result = 0;

      while (Numbers[Index] != '\0' && Numbers[Index] != '#')
      {
        if (Numbers[Index] <= '9' && Numbers[Index] >= '0')
        {
          JustNumber += Numbers[Index];
          // this is for the while loop that happens before this state starts 
          Iteration++;
        }
        Index++;
        // making sure where in bonds 
        if (Index > Numbers.Length - 1) { break; }
      }
      int.TryParse(JustNumber, out Result);
      return Result;
    }// end function 
    /// <summary>
    /// this is where we put the data from the compiler to the screen(or DataGrid depending one the case) 
    /// </summary>
    /// <param name="CompilerData"></param>
    /// <param name="GridView"></param>
    /// <param name="ErrorText"></param>
    private void ExacuteParams(String[] CompilerData, ref DataGridViewRow GridView, ref DataGridView DataView, ref TextBox ErrorText)
    {
      int IterationCount = 1;
      /*! \todo add the syntactic and semantic parsing later */
      for (int i = 0; i < m_OrderOfParse.Count; ++i)
      {

        switch (m_OrderOfParse[i])
        {
          case ParseModes.UNKNOWN:
            break;
          case ParseModes.ErrorReading:
            InsertError(CompilerData, ref ErrorText, ref IterationCount, m_ParamArgsCount[i]);
            break;
          case ParseModes.LexReading:
            InsertLex(CompilerData, ref GridView,ref DataView, ref IterationCount, m_ParamArgsCount[i]);
            break;
          case ParseModes.SytaxReading:
            break;
          case ParseModes.SemanticReading:
            break;
        }

      }// end for 


    }// end function 
    /// <summary>
    /// This function takes care of inserting the error related with compilation
    /// </summary>
    /// <param name="CompilerData"></param>
    /// <param name="ErrorText"></param>
    /// <param name="IterationCount"></param>
    /// <param name="ParamCount"></param>
    private void InsertError(String[] CompilerData, ref TextBox ErrorText, ref int IterationCount, int ParamCount)
    {
      int CompilerEndPos = IterationCount + ParamCount;

      ErrorText.Text = m_ErrorInfo;
      if(ParamCount == 0)
      {
        ErrorText.Text = "=====================NO ERROR GENERATED======================\r\n";
      }
      else
      {
        for (int i = CompilerEndPos; IterationCount < i; ++IterationCount)
        {
          ErrorText.Text += CompilerData[IterationCount] + "\r\n";
        }
      }

    }// end function

    private void InsertLex(String[] CompilerData, ref DataGridViewRow GridView,ref DataGridView DataView, ref int IterationCount, int ParamCount)
    {
      GridView.CreateCells(DataView);
      // here goes the respective components of lexical analysis
      String Lexema = "";
      String Type = "";
      String Line = "";

      Byte LexArgCount = 1;
      int CompilerEndPos = IterationCount + ParamCount;

      for (int i = CompilerEndPos; IterationCount < i; ++IterationCount)
      {
        foreach (char chr in CompilerData[IterationCount])
        {

          if (chr != '~' && LexArgCount % 3 == 1)
          {
            Lexema += chr;
          }
          else if (chr != '~' && LexArgCount % 3 == 2)
          {
            Type += chr;
          }
          else if (chr != '~' && LexArgCount % 3 == 0)
          {
            Line += chr;
          }

          else { LexArgCount++; }
        }// end foreach
        LexArgCount = 1;
        DataGridViewRow dataGridView = new DataGridViewRow();

        dataGridView.CreateCells(DataView);

        dataGridView.Cells[0].Value = Lexema;
        dataGridView.Cells[1].Value = Line;
        dataGridView.Cells[2].Value = Type;

        DataView.Rows.Add(dataGridView);

        Lexema = "";
        Type = "";
        Line = "";
      }// end for 

    }// end function 


  }/// End class 
}