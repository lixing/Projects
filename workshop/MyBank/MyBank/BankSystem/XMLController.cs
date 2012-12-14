using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace BankSystem
{

    public class XMLController
    {

        private string _XMLFileName;

        public string XMLFileName
        {
            get { return _XMLFileName; }
            set { _XMLFileName = value; }
        }



        public XMLController(string XMLFileName)
        {
            _XMLFileName = XMLFileName;
        }

        public List<string> ReadAllSection()
        {
            List<string> result = new List<string>();
            if (System.IO.File.Exists(_XMLFileName) == true)
            {

                XmlDocument dom_document = new XmlDocument();
                dom_document.Load(_XMLFileName);
                foreach (XmlNode Rootchild_node in dom_document.DocumentElement.ChildNodes)
                {
                    
                    result.Add(Rootchild_node.Name);

                }
            }
            return result;
        }


        public string Read(string SectionName, string KeyName)
        {
            if (System.IO.File.Exists(_XMLFileName) == true)
            {
                XmlDocument dom_document = new XmlDocument();
                dom_document.Load(_XMLFileName);

                foreach (XmlNode Rootchild_node in dom_document.DocumentElement.ChildNodes)
                {

                    if (Rootchild_node.Name == SectionName)
                    {

                        foreach (XmlNode child_node in Rootchild_node.ChildNodes)
                        {
                            if (child_node.Name == KeyName)
                            {
                                return child_node.InnerText;
                            }
                        }
                    }
                }
            }
            else
            {

                return "";
            }

            return "";
        }



      


        public bool Write(string SectionName, string KeyName, string Value)
        {
            try
            {
                if (System.IO.File.Exists(_XMLFileName) == true)
                {

                    XmlDocument dom_document = new XmlDocument();
                    dom_document.Load(_XMLFileName);

                    foreach (XmlNode Rootchild_node in dom_document.DocumentElement.ChildNodes)
                    {
                        if (Rootchild_node.Name == SectionName)
                        {

                            foreach (XmlNode KeyNode in Rootchild_node.ChildNodes)
                            {

                                if (KeyNode.Name.Equals(KeyName))
                                {

                                    KeyNode.InnerText = Value;
                                    dom_document.Save(_XMLFileName);
                                    return true;

                                }
                            }


                            XmlNode node = dom_document.CreateElement(KeyName);
                            Rootchild_node.AppendChild(node);
                            node.InnerText = Value;
                            dom_document.Save(_XMLFileName);
                            return true;
                        }
                    }



                    XmlNode SectionNode = dom_document.CreateElement(SectionName);
                    dom_document.DocumentElement.AppendChild(SectionNode);
                    XmlNode Key_Node = default(XmlNode);
                    Key_Node = dom_document.CreateElement(KeyName);
                    Key_Node.InnerText = Value;
                    SectionNode.AppendChild(Key_Node);

                    dom_document.Save(_XMLFileName);

                    return true;
                }
                else
                {



                    XmlDocument dom_document = new XmlDocument();
                    XmlNode Root_node = dom_document.CreateElement("XMLConfigFile");
                    dom_document.AppendChild(Root_node);

                    XmlNode SectionNode = dom_document.CreateElement(SectionName);
                    Root_node.AppendChild(SectionNode);

                    XmlNode KeyNode = dom_document.CreateElement(KeyName);
                    SectionNode.AppendChild(KeyNode);

                    KeyNode.InnerText = Value;
                    dom_document.Save(_XMLFileName);

                    return true;

                }
            }
            catch (Exception ex)
            {

                Console.WriteLine(ex.Message);

                return false;
            }
        }



    }
}
