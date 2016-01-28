using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace caesar_Csharp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            char[] arr = textBox1.Text.ToCharArray();
            int i;
            for (i = 0; i < arr.Length; i++)
            {
                int tmp = (int)arr[i];
                if (tmp >= 97 && tmp <= (int)'z')
                    tmp = 97 + (tmp - 97 + 5) % 26;
                else if (tmp >= 65 && tmp <= 'Z')
                    tmp = 65 + (tmp - 65 + 5) % 26;
                arr[i] = (char)tmp;
            }
            textBox2.Text = new string(arr);
        }


        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            label1.Text = "plaintext";
            label2.Text = "ciphertext";
        }
    }
}
