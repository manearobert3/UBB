// See https://aka.ms/new-console-template for more information
using System.Net.NetworkInformation;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using Lab2Tema;
using System.Diagnostics;
using static System.Runtime.InteropServices.JavaScript.JSType;


class MainClass() { 

    static void Tests()
    {
      
        BasicValidation stringObject = new BasicValidation();

        // Asserts for the phone number validator function:

        Debug.Assert(stringObject.validatePhoneNumber("194 83"));
        Debug.Assert(!stringObject.validatePhoneNumber("asd"));
        Debug.Assert(stringObject.validatePhoneNumber("+04 743 234 234"));
        Debug.Assert(stringObject.validatePhoneNumber("-(04) 199 299 399"));
        Debug.Assert(!stringObject.validatePhoneNumber("#102 120"));
        Debug.Assert(stringObject.validatePhoneNumber("-1020-120"));

        //Asserts for the email validator function

        Debug.Assert(stringObject.validateEmail("a@sdfio.com"));
        Debug.Assert(stringObject.validateEmail("andrei@gmail.com"));
        Debug.Assert(!stringObject.validateEmail("andrei.com"));
        Debug.Assert(!stringObject.validateEmail("andrei@gmail"));
        Debug.Assert(!stringObject.validateEmail("andrei@gmailcom"));

        //Asserts for the date validator function

        Debug.Assert(stringObject.validateDate("12-14-2012"));
        Debug.Assert(stringObject.validateDate("13-11-2012"));
        Debug.Assert(!stringObject.validateDate("13-13-2012"));
        Debug.Assert(!stringObject.validateDate("123-14-2012"));
        Debug.Assert(!stringObject.validateDate("12-14-20122"));

        //Asserts for the sanitization function

        Debug.Assert(stringObject.sanitizeString("!=3%#|a|OR")=="3a");
        Debug.Assert(stringObject.sanitizeString("Doneasd") == "asd");
        Debug.Assert(stringObject.sanitizeString("dOnE") == "");
        Debug.Assert(stringObject.sanitizeString("3333OR") == "3333");


    }
    static void Main()
    {       
        Tests();
        
    }
}


