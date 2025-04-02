using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace graphics_editor
{
    public abstract class Shape
    {
        protected int x;
        protected int y;
        public int Id = new Random().Next();
        protected string Color;

        public Shape(string color)
        {
            this.Color = color;
        }

        public Shape(Shape shape, int x, int y)
        {
            this.Color = shape.Color;
            this.x = x;
            this.y = y;
        }

        public System.Drawing.Color getColor(string color)
        {
            if (color == "red")
            {
                return System.Drawing.Color.Red;
            }
            else if (color == "blue")
            {
                return System.Drawing.Color.Green;
            }
            else
            {
                return System.Drawing.Color.Blue;
            }
        }

        public void MoveTo(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        public abstract Shape Clone(int x, int y);
        public abstract void Draw(Graphics g);
        public abstract bool Contains(Point point);
    }

    public class Rectangle : Shape
    {
        public int Width { get; set; }
        public int Height { get; set; }

        public Rectangle(Rectangle source, int x, int y)
            : base(source, x, y)
        {
            Width = source.Width;
            Height = source.Height;
        }

        public Rectangle(int width, int height, string color)
            : base(color)
        {
            Width = width;
            Height = height;
        }

        public override Shape Clone(int x, int y)
        {
            return new Rectangle(this, x, y);
        }

        public override void Draw(Graphics g)
        {
            using (Pen pen = new Pen(getColor(base.Color)))
            {
                g.DrawRectangle(pen, x, y, Width, Height);
            }
        }

        public override bool Contains(Point point)
        {
            return point.X >= x && point.X <= x + Width && point.Y >= y && point.Y <= y + Height;
        }
    }

    public class Circle : Shape
    {
        public int Radius { get; set; }

        public Circle(Circle source, int x, int y)
            : base(source, x, y)
        {
            Radius = source.Radius;
        }

        public Circle(int radius, string color)
            : base(color)
        {
            Radius = radius;
        }

        public override Shape Clone(int x, int y)
        {
            return new Circle(this, x, y);
        }

        public override void Draw(Graphics g)
        {
            using (Pen pen = new Pen(getColor(base.Color)))
            {
                g.DrawEllipse(pen, x - Radius, y - Radius, Radius * 2, Radius * 2);
            }
        }

        public override bool Contains(Point point)
        {
            double distance = Math.Sqrt(Math.Pow(point.X - x, 2) + Math.Pow(point.Y - y, 2));

            return distance <= Radius;
        }
    }

    public class Square : Shape
    {
        public int Side { get; set; }

        public Square(Square source, int x, int y)
            : base(source, x, y)
        {
            this.Side = source.Side;
        }

        public Square(int side, string color)
            : base(color)
        {
            Side = side;
        }

        public override Shape Clone(int x, int y)
        {
            return new Square(this, x, y);
        }

        public override void Draw(Graphics g)
        {
            using (Pen pen = new Pen(getColor(base.Color)))
            {
                g.DrawRectangle(pen, x, y, Side, Side);
            }
        }

        public override bool Contains(Point point)
        {
            return point.X >= x && point.X <= x + Side && point.Y >= y && point.Y <= y + Side;
        }
    }
}
