using System;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;

namespace SSControls
{
    public partial class SSChart : UserControl
    {
        private Timer RedrawTimer;
        private Bitmap _backbuffer;
        public bool redrawactive;

        protected override void OnSizeChanged(EventArgs e)
        {
            if (_backbuffer != null)
            {
                _backbuffer.Dispose();
                _backbuffer = null;
            }
            if (!_scaleonresize)
            {
                Page.Width = this.Width;
                Page.Height = this.Height;
            }
            if (RedrawTimer == null)
            {
                RedrawTimer = new Timer();
                RedrawTimer.Tick += RedrawTimer_Tick;
                RedrawTimer.Interval = 100;
                RedrawTimer.Start();
            }
            Invalidate();
            base.OnSizeChanged(e);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            if (_backbuffer != null)
            {
                e.Graphics.DrawImageUnscaled(_backbuffer, 0, 0);
            }
        }


        protected override void OnPaintBackground(PaintEventArgs e)
        {
            //MyBase.OnPaintBackground(e)
        }

        public class GMargins
        {
            private float _left = 50;
            private float _right = 35;
            private float _top = 30;
            private float _bottom = 30;

            public event ChangedEventHandler Changed;
            public delegate void ChangedEventHandler();

            public float Left
            {
                get { return _left; }
                set
                {
                    if (_left != value)
                    {
                        _left = value;
                        Changed?.Invoke();
                    }
                }
            }

            public float Right
            {
                get { return _right; }
                set
                {
                    if (_right != value)
                    {
                        _right = value;
                        Changed?.Invoke();
                    }
                }
            }

            public float Top
            {
                get { return _top; }
                set
                {
                    if (_top != value)
                    {
                        _top = value;
                        Changed?.Invoke();
                    }
                }
            }

            public float Bottom
            {
                get { return _bottom; }
                set
                {
                    if (_bottom != value)
                    {
                        _bottom = value;
                        Changed?.Invoke();
                    }
                }
            }

        }

        public class GPage
        {
            private float _width = 400;
            private float _height = 300;
            public event ChangedEventHandler Changed;
            public delegate void ChangedEventHandler();
            public GMargins Margins = new GMargins();            

            public GPage()
            {
                Margins.Changed += Margins_Changed;
            }

            public float Width
            {
                get { return _width; }
                set
                {
                    if (_width != value)
                    {
                        if (value > Margins.Left + Margins.Right)
                        {
                            _width = value;
                            Changed?.Invoke();
                        }
                    }
                }
            }

            public float Height
            {
                get { return _height; }
                set
                {
                    if (_height != value)
                    {
                        if (value > Margins.Top + Margins.Bottom)
                        {
                            _height = value;
                            Changed?.Invoke();
                        }
                    }
                }
            }

            public float DrawWidth
            {
                get { return _width - Margins.Left - Margins.Right; }
            }

            public float DrawHeight
            {
                get { return _height - Margins.Top - Margins.Bottom; }
            }

            private void Margins_Changed()
            {
                Changed?.Invoke();
            }

        }

        public class GScale
        {
            public enum GScaleTypes : byte
            {
                HorBottom = 0,
                HorTop = 1,
                VerLeft = 2,
                VerRight = 3
            }


            private GScaleTypes _scaletype = GScaleTypes.HorBottom;
            public GScaleTypes ScaleType
            {
                get { return _scaletype; }
                set
                {
                    switch (value)
                    {
                        case GScaleTypes.HorTop:
                            ValSFormat.Alignment = StringAlignment.Center;
                            ValSFormat.LineAlignment = StringAlignment.Far;
                            break;
                        case GScaleTypes.VerLeft:
                            ValSFormat.Alignment = StringAlignment.Far;
                            ValSFormat.LineAlignment = StringAlignment.Center;
                            break;
                        case GScaleTypes.VerRight:
                            ValSFormat.Alignment = StringAlignment.Near;
                            ValSFormat.LineAlignment = StringAlignment.Center;
                            break;
                        default:
                            ValSFormat.Alignment = StringAlignment.Center;
                            ValSFormat.LineAlignment = StringAlignment.Near;
                            break;
                    }
                    _scaletype = value;
                }
            }

            public bool PaintOver = false;
            public float ValFrom = 0;
            public float ValTo = 100;
            public float ValMinStep = 5;
            public float ValMajStep = 10;
            public float ValMinSize = 2;
            public float ValMajSize = 4;
            public float sX = 0;
            public float sY = 0;
            public Pen Pen = new Pen(Brushes.White);
            public bool Visible = false;
            public Font ValFont = (Font)SystemFonts.SmallCaptionFont.Clone();
            public string ValFormat = "0.00";
            public bool ValVisible = true;
            public StringFormat ValSFormat = new StringFormat();
            public float ValOffset = 0;
            public Brush ValBrush = new SolidBrush(Color.Aquamarine);
            public bool ShowMinLines = true;
            public Pen MinLinesPen = new Pen(new SolidBrush(Color.FromArgb(0x60606060)));
            public bool ShowMajLines = true;
            public Pen MajLinesPen = new Pen(new SolidBrush(Color.FromArgb(unchecked((int)0x90909090))));

            public GScale()
            {
                var _with1 = ValSFormat;
                _with1.Alignment = StringAlignment.Center;
                _with1.LineAlignment = StringAlignment.Near;
                Pen.Width = (float)0.000001;
            }

            public void Dispose()
            {
                if (Pen != null) Pen.Dispose();
                if (ValFont != null) ValFont.Dispose();
                if (ValSFormat != null) ValSFormat.Dispose();
                if (ValBrush != null) ValBrush.Dispose();
                if (MinLinesPen != null) MinLinesPen.Dispose();
                if (MajLinesPen != null) MajLinesPen.Dispose();
                Pen = null;
                ValFont = null;
                ValSFormat = null;
                ValBrush = null;
                MinLinesPen = null;
                MajLinesPen = null;
            }

            public void Draw(ref Graphics g, ref GPage p)
            {
                float s = 0;
                float s1 = 0;
                float s2 = 0;
                float eX = 0;
                float eY = 0;
                float majXOff = 0;
                float majYoff = 0;
                float minXoff = 0;
                float minYoff = 0;
                float vXoff = 0;
                float vYoff = 0;
                if (Visible)
                {
                    switch (_scaletype)
                    {
                        case GScaleTypes.HorBottom:
                            eX = sX + p.DrawWidth;
                            eY = sY;
                            majXOff = 0;
                            majYoff = ValMajSize;
                            minXoff = 0;
                            minYoff = ValMinSize;
                            vXoff = 0;
                            vYoff = ValOffset + ValMajSize;
                            break;
                        case GScaleTypes.HorTop:
                            eX = sX + p.DrawWidth;
                            eY = sY;
                            majXOff = 0;
                            majYoff = -ValMajSize;
                            minXoff = 0;
                            minYoff = -ValMinSize;
                            vXoff = 0;
                            vYoff = -ValOffset - ValMajSize;
                            break;
                        case GScaleTypes.VerLeft:
                            eX = sX;
                            eY = sY - p.DrawHeight;
                            majXOff = -ValMajSize;
                            majYoff = 0;
                            minXoff = -ValMinSize;
                            minYoff = 0;
                            vXoff = -ValOffset - ValMajSize;
                            vYoff = 0;
                            break;
                        case GScaleTypes.VerRight:
                            eX = sX;
                            eY = sY - p.DrawHeight;
                            majXOff = ValMajSize;
                            majYoff = 0;
                            minXoff = ValMinSize;
                            minYoff = 0;
                            vXoff = ValOffset + ValMajSize;
                            vYoff = 0;
                            break;
                    }
                    if (ValFrom != ValTo)
                    {
                        g.DrawLine(Pen, sX, sY, eX, eY);
                        if (ValMinStep > 0)
                        {
                            for (s = ValFrom; s <= ValTo; s += ValMinStep)
                            {
                                s1 = sX + (((s - ValFrom) / (ValTo - ValFrom))) * (eX - sX);
                                s2 = sY + (((s - ValFrom) / (ValTo - ValFrom))) * (eY - sY);
                                g.DrawLine(Pen, s1, s2, s1 + minXoff, s2 + minYoff);
                                if (ShowMinLines)
                                {
                                    switch (_scaletype)
                                    {
                                        case GScaleTypes.VerRight:
                                        case GScaleTypes.VerLeft:
                                            g.DrawLine(MinLinesPen, 0, s2, p.DrawWidth, s2);
                                            break;
                                        default:
                                            g.DrawLine(MinLinesPen, s1, 0, s1, -p.DrawHeight);
                                            break;
                                    }
                                }
                            }
                        }
                        if (ValMajStep > 0)
                        {
                            for (s = ValFrom; s <= ValTo; s += ValMajStep)
                            {
                                s1 = sX + (((s - ValFrom) / (ValTo - ValFrom))) * (eX - sX);
                                s2 = sY + (((s - ValFrom) / (ValTo - ValFrom))) * (eY - sY);
                                g.DrawLine(Pen, s1, s2, s1 + majXOff, s2 + majYoff);
                                if (ShowMajLines)
                                {
                                    switch (_scaletype)
                                    {
                                        case GScaleTypes.VerRight:
                                        case GScaleTypes.VerLeft:
                                            g.DrawLine(MajLinesPen, 0, s2, p.DrawWidth, s2);
                                            break;
                                        default:
                                            g.DrawLine(MajLinesPen, s1, 0, s1, -p.DrawHeight);
                                            break;
                                    }
                                }
                                if (ValVisible)
                                {
                                    g.DrawString(s.ToString(ValFormat), ValFont, ValBrush, s1 + vXoff, s2 + vYoff, ValSFormat);
                                }
                            }
                        }
                    }
                }
            }
        }

        public class GDrawing
        {
            public bool Visible = true;
            public Boolean ShowPoints = false;
            public Pen Pen = new Pen(Brushes.Red);
            public GScale XScale;
            public GScale Yscale;
            public PointF[] Points;
            public long PointsNum
            {
                get
                {
                    if (Points == null)
                    {
                        return 0;
                    }
                    else
                    {
                        try
                        {
                            return Points.Length;
                        }
                        catch
                        {
                            return 0;
                        }
                    }
                }
                set
                {
                    long oldnum = 0;
                    long i = 0;
                    oldnum = PointsNum;
                    if (oldnum != value)
                    {
                        if (value > 0)
                        {
                            Array.Resize(ref Points, (int)value);
                            for (i = oldnum; i < value; i++)
                            {
                                Points[i] = new PointF();
                            }
                        }
                        else
                        {
                            Points = null;
                        }
                    }
                }
            }


            public void Draw(ref Graphics g, ref GPage p)
            {
                Matrix m = null;
                float[] mtx = null;
                m = g.Transform.Clone();

                g.ScaleTransform(p.DrawWidth / (XScale.ValTo - XScale.ValFrom), -p.DrawHeight / (Yscale.ValTo - Yscale.ValFrom));
                g.TranslateTransform(XScale.ValFrom, -Yscale.ValFrom);

                Pen.ResetTransform();
                mtx = g.Transform.Elements;
                Pen.ScaleTransform(1 / mtx[0], 1 / mtx[3]);
                Pen.TranslateTransform(0, 0);
                if (Points != null) {
                    g.DrawLines(Pen, Points);
                    if (ShowPoints) {
                        var c = Pen.Color;
                        Pen.Color = Color.FromArgb(255 - Pen.Color.R, 255 - Pen.Color.G, 255 - Pen.Color.B);
                        g.DrawRectangles(Pen, Points.Select(x => new RectangleF(x.X, x.Y, (float)0.01,1)).ToArray());
                        Pen.Color = c;
                    }
                }
                g.Transform.Dispose();
                g.Transform = m;
            }

            ~GDrawing()
            {
                Pen.Dispose();
            }

        }

        public GPage Page = new GPage();
        private bool _scaleonresize = false;
        private GScale[] _scales;
        private GDrawing[] _drawings;

        public bool ScaleOnResize
        {
            get { return _scaleonresize; }
            set { _scaleonresize = value; }
        }


        public GScale Scales(int index)
        {
            return _scales[index];
        }

        public GDrawing Drawings(int index)
        {
            return _drawings[index];
        }

        public GDrawing[] Drawings1
        {
            get { return _drawings; }
        }

        public long ScaleNum
        {
            get
            {
                if (_scales == null)
                {
                    return 0;
                }
                else
                {
                    try
                    {
                        return _scales.Length;
                    }
                    catch
                    {
                        return 0;
                    }
                }
            }
            set
            {
                long i = 0;
                long oldnum = 0;
                oldnum = ScaleNum;
                if (oldnum != value)
                {
                    if (value > 0)
                    {
                        for (i = value; i <= oldnum - 1; i++)
                        {
                            _scales[i] = null;
                        }
                        Array.Resize(ref _scales, (int)value);
                        for (i = oldnum; i <= value - 1; i++)
                        {
                            _scales[i] = new GScale();
                        }
                    }
                    else
                    {
                        for (i = 0; i <= ScaleNum - 1; i++)
                        {
                            _scales[i] = null;
                        }
                        _scales = null;
                    }
                }
            }
        }

        public long DrawingsNum
        {
            get
            {
                if (_drawings == null)
                {
                    return 0;
                }
                else
                {
                    try
                    {
                        return _drawings.Length;
                    }
                    catch
                    {
                        return 0;
                    }
                }
            }
            set
            {
                long i = 0;
                long oldnum = 0;
                oldnum = DrawingsNum;
                if (oldnum != value)
                {
                    if (value != 0)
                    {
                        for (i = value; i <= oldnum - 1; i++)
                        {
                            _drawings[i] = null;
                        }
                        Array.Resize(ref _drawings, (int)value);
                        for (i = oldnum; i <= value - 1; i++)
                        {
                            _drawings[i] = new GDrawing();
                        }
                    }
                    else
                    {
                        for (i = 0; i <= oldnum - 1; i++)
                        {
                            _drawings[i] = null;
                        }
                        _drawings = null;
                    }
                }
            }
        }

        public void _Redraw()
        {
            long i = 0;
            redrawactive = true;
            _backbuffer = null;
            if (_backbuffer == null)
            {
                _backbuffer = new Bitmap(Math.Max(this.ClientSize.Width, 2), Math.Max(this.ClientSize.Height, 2));
                Graphics g = Graphics.FromImage(_backbuffer);

                g.ScaleTransform(Math.Max(this.Width, 2) / Page.Width, Math.Max(this.Height, 2) / Page.Height);
                g.TranslateTransform(Page.Margins.Left, Page.Height - Page.Margins.Bottom);
                g.Clear(BackColor);

                g.SmoothingMode = SmoothingMode.HighSpeed;
                for (i = 0; i <= ScaleNum - 1; i++)
                {
                    if(!_scales[i].PaintOver) _scales[i].Draw(ref g, ref Page);
                }

                g.SmoothingMode = SmoothingMode.HighQuality;
                foreach(var d in _drawings)
                {
                    if (d.Visible) d.Draw(ref g, ref Page);
                }

                g.SmoothingMode = SmoothingMode.HighSpeed;
                for (i = 0; i <= ScaleNum - 1; i++)
                {
                    if (_scales[i].PaintOver) _scales[i].Draw(ref g, ref Page);
                }

                g.Dispose();
                if (!this.IsDisposed)
                {
                    g = this.CreateGraphics();
                    g.DrawImageUnscaled(_backbuffer, 0, 0);
                    g.Dispose();
                }
            }
            Application.DoEvents();
            redrawactive = false;
        }

        public SSChart()
        {
            long i = 0;
            // This call is required by the designer.
            InitializeComponent();

            // Add any initialization after the InitializeComponent() call.
            ScaleNum = 2;
            _scales[0].ScaleType = GScale.GScaleTypes.HorBottom;
            _scales[0].Visible = true;
            _scales[0].sX = 0;
            _scales[0].sY = 0;
            _scales[0].Pen.Width = 1;

            _scales[1].ScaleType = GScale.GScaleTypes.VerLeft;
            _scales[1].Visible = true;
            _scales[1].sX = 0;
            _scales[1].sY = 0;
            _scales[1].Pen.Width = 1;

            DrawingsNum = 1;
            _drawings[0].Pen.Width = 1;
            _drawings[0].XScale = Scales(0);
            _drawings[0].Yscale = Scales(0);
            _drawings[0].PointsNum = 1000;
            Random r = new Random();
            for (i = 0; i <= _drawings[0].PointsNum - 1; i++)
            {
                _drawings[0].Points[i].X = Convert.ToSingle(i) / 10;
                _drawings[0].Points[i].Y = (float)(r.Next(0, 50) + Math.Sin(i / 50) * 25 + 25);
            }

        }

        private void RedrawTimer_Tick(object sender, EventArgs e)
        {
            RedrawTimer.Stop();
            RedrawTimer.Tick -= RedrawTimer_Tick;
            RedrawTimer.Dispose();
            RedrawTimer = null;
            _Redraw();
        }

    }
}
