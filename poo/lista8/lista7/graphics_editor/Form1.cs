using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace graphics_editor
{
    public partial class Form1 : Form
    {
        Stack<ShapeMemento> undoStates = new Stack<ShapeMemento>();
        Stack<ShapeMemento> redoStates = new Stack<ShapeMemento>();
        Point startpoint;

        public class ShapeMemento
        {
            public string type; // move, remove
            public Shape shape;
            public Point location;
            public Point newLocation;
            public int id;

            public ShapeMemento(string type, Shape shape, Point location, Point newLocation, int id)
            {
                this.type = type;
                this.shape = shape;
                this.location = location;
                this.newLocation = newLocation;
                this.id = id;
            }
        }

        void CreateMemento(ShapeMemento memento)
        {
            undoStates.Push(memento);
            redoStates.Clear();
        }

        public void Undo()
        {
            if (undoStates.Count > 0)
            {
                ShapeMemento currentState = undoStates.Pop();
                redoStates.Push(currentState);
                RevokeMemento(currentState);
            }
        }

        public void Redo()
        {
            if (redoStates.Count > 0)
            {
                ShapeMemento futureState = redoStates.Pop();
                undoStates.Push(futureState);
                this.RestoreMemento(futureState);
            }
        }

        void RestoreMemento(ShapeMemento memento)
        {
            if (memento.type == "Move")
            {
                Shape shape = shapes.Find(s => s.Id == memento.id);
                if (shape != null)
                {
                    shape.MoveTo(memento.newLocation.X, memento.newLocation.Y);
                }
            }
            else if (memento.type == "Remove")
            {
                Shape shape = shapes.Find(s => s.Id == memento.id);
                if (shape != null)
                {
                    shapes.Remove(shape);
                }
            }
            else
            {
                shapes.Add(memento.shape);
            }
            panel1.Invalidate();
        }

        void RevokeMemento(ShapeMemento memento)
        {
            if (memento.type == "Remove")
            {
                shapes.Add(memento.shape);
            }
            else if (memento.type == "Add")
            {
                Shape shape = shapes.Find(s => s.Id == memento.id);
                if (shape != null)
                {
                    shapes.Remove(shape);
                }
            }
            else if (memento.type == "Move")
            {
                Shape shape = shapes.Find(s => s.Id == memento.id);
                if (shape != null)
                {
                    shape.MoveTo(memento.location.X, memento.location.Y);
                }
            }
            panel1.Invalidate();
        }

        private string Mode;
        private int movedId = -1;
        private readonly List<Shape> shapes = new List<Shape>();
        private readonly List<Shape> baseShapes = new List<Shape>
        {
            new Rectangle(50, 75, "red"),
            new Square(50, "green"),
            new Circle(30, "blue")
        };

        public Form1()
        {
            InitializeComponent();
        }

        private void toolStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            Mode = "Circle";
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            Mode = "Square";
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            Mode = "Rectangle";
        }

        private void toolStripButton4_Click(object sender, EventArgs e)
        {
            Mode = "Move";
        }

        private void toolStripButton5_Click(object sender, EventArgs e)
        {
            Mode = "Remove";
        }

        private void toolStripButton6_Click(object sender, EventArgs e)
        {
            Mode = "Undo";
            Undo();
        }

        private void toolStripButton7_Click(object sender, EventArgs e)
        {
            Mode = "Redo";
            Redo();
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (Mode == "Circle" || Mode == "Rectangle" || Mode == "Square")
            {
                List<string> modes = new List<string> { "Rectangle", "Square", "Circle" };
                int index = modes.IndexOf(Mode);

                var shape = baseShapes[index].Clone(e.X, e.Y);
                shapes.Add(shape);
                ShapeMemento memento = new ShapeMemento(
                    "Add",
                    shape,
                    e.Location,
                    e.Location,
                    shape.Id
                );
                CreateMemento(memento);
                panel1.Invalidate();
            }

            if (Mode == "Move")
            {
                foreach (Shape shape in shapes)
                {
                    if (shape.Contains(e.Location))
                    {
                        movedId = shape.Id;
                        startpoint = e.Location;
                        return;
                    }
                }
            }

            if (Mode == "Remove")
            {
                foreach (Shape shape in shapes)
                    if (shape.Contains(e.Location))
                    {
                        shapes.Remove(shape);
                        panel1.Invalidate();
                        ShapeMemento memento = new ShapeMemento(
                            "Remove",
                            shape,
                            e.Location,
                            e.Location,
                            shape.Id
                        );
                        CreateMemento(memento);
                        return;
                    }
            }
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (movedId != -1)
            {
                Shape movedShape = shapes.FirstOrDefault(shape => shape.Id == movedId);
                if (movedShape != null)
                {
                    movedShape.MoveTo(e.X, e.Y);
                    panel1.Invalidate();
                }
            }
        }

        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            if (movedId != -1)
            {
                ShapeMemento memento = new ShapeMemento(
                    "Move",
                    null,
                    startpoint,
                    e.Location,
                    movedId
                );
                CreateMemento(memento);
                movedId = -1;
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            foreach (Shape shape in shapes)
            {
                shape.Draw(e.Graphics);
            }
        }
    }
}
