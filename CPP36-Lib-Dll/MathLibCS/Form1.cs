using System;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;


namespace MathLibCS
{
    public partial class Form1 : Form
    {
        [System.Runtime.InteropServices.DllImport("MathDll.dll")]
        public static extern float maxVal(float x, float y);

        [System.Runtime.InteropServices.DllImport("MathDll.dll")]
        public static extern float mean(float[] data, int N);
        //unsafe public static extern float mean(float* data, int N);

        [System.Runtime.InteropServices.DllImport("MathDll.dll")]
        //unsafe public static extern IntPtr load_image(char* filename, int* W, int* H, int* step);
        public static extern IntPtr load_image([MarshalAs(UnmanagedType.LPWStr)] string filename, ref int W, ref int H, ref int step);

        public Form1()
        {
            InitializeComponent();
        }

        private void btnCallDLL_Click(object sender, EventArgs e)
        {
            //string s = System.IO.Directory.GetCurrentDirectory();
            //MessageBox.Show(s);
            //float m = maxVal(121, 125);

            float[] data = new float[4];
            data[0] = 5;
            data[1] = 15;
            data[2] = 45;
            data[3] = 21;
            float m = mean(data, 4);
            MessageBox.Show(m.ToString());

            /*unsafe
            {
                fixed (float* p = &data[0])
                { 
                    float m = mean(p, 4);
                    MessageBox.Show(m.ToString());
                }
            }*/
        }

        private void btnLoadImage_Click(object sender, EventArgs e)
        {
            int W = 0, H = 0, step = 0;
            //char[] str = new char[100];
            string fn = "D:\\1.jpg";
            IntPtr ptr;
            /*unsafe
            {
                fixed (char* p = &str[0])
                {
                    for (int i = 0; i < fn.Length; i++)
                        str[i] = fn[i];
                    ptr = load_image(p, &W, &H, &step);
                }
            }*/
            ptr = load_image(fn, ref W, ref H, ref step);
            Bitmap frame = new Bitmap(W, H, step, System.Drawing.Imaging.PixelFormat.Format24bppRgb, ptr);
            pictureBox1.Image = frame;
        }
    }
}
