using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Lab2Tema
{
    class BasicValidation
    {
        public BasicValidation()
        { }
        public Boolean validatePhoneNumber(string phoneNumber)
        {
            if (Regex.Match(phoneNumber, "^[0-9+\\-() ]+$").Success)
            {
                return true;
            }
            return false;
        }


        public Boolean validateEmail(string email)
        {
            if (Regex.Match(email, "^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$").Success)
            {
                return true;
            }
            return false;
        }

        public Boolean validateDate(string date)
        {

            return Regex.Match(date, "^(3[01]|[12][0-9]|0?[1-9])(\\/|-)(1[0-2]|0?[1-9])\\2([0-9]{2})?[0-9]{2}$").Success || Regex.Match(date, "^(1[0-2]|0?[1-9])(\\/|-)(3[01]|[12][0-9]|0?[1-9])\\2([0-9]{2})?[0-9]{2}$").Success;
        }
        public Boolean validateTime(string time) { return true; }

        private string ReplaceIgnoreCase(string search, string find, string replace)
        {
            return Regex.Replace(search ?? "", Regex.Escape(find ?? ""), (replace ?? "").Replace("$", "$$"), RegexOptions.IgnoreCase);
        }

        public string sanitizeString(string stringToSanitize)
        {
            string[] stringVector = new string[10];
            stringVector = ["OR", "UNION", "DROP", "DELETE", "TRUNCATE", "SELECT", "UPDATE", "INSERT", "LIKE", "DONE"];
            string newString;
            newString = Regex.Replace(stringToSanitize, @"[\[\]'\-#%*;+><=(\!=)(\|)]+", "");
            for (int i = 0; i <= 9; i++)
            {
                newString = this.ReplaceIgnoreCase(newString, stringVector[i], "");
            }

            return newString;

        }
    }
}
