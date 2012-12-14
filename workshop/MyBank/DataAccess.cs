using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace TestXML
{
    class DataAccess
    {
        public void AddQuestion(string type, string answer)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load("Questions.xml");

            //string s = "//Question[@type=" + type + "]";
            XmlNode node = doc.SelectSingleNode("//Question[@type='" + type + "']");
            if (node != null)
            {
                if (node.Attributes[1].Value != answer)
                    node.Attributes[1].Value = answer;
            }
            else
            {
                XmlElement Question = doc.CreateElement("Question");
                Question.SetAttribute("type", type);
                Question.SetAttribute("answer", answer);
                XmlNode questionNode = doc.SelectSingleNode("//Questions");
                questionNode.AppendChild(Question);
            }
            XmlTextWriter tw = new XmlTextWriter("Questions.xml", null);
            tw.Formatting = Formatting.Indented;
            doc.WriteContentTo(tw);
            tw.Close();
        }

        public string getAnswer(string type)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load("Questions.xml");

            XmlNode node = doc.SelectSingleNode("//Question[@type='" + type + "']");
            if (node != null)
            {
                return (node.Attributes[1].Value);
            }
            return "";
        }
    }
}
