using System.Windows.Forms;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.Geometry;

namespace AutocadPlugin1
{
    public class Commands : IExtensionApplication
    {
        public void Initialize()
        {
            MessageBox.Show("Hello!");
        }

        public void Terminate()
        {
            MessageBox.Show("Goodbye!");
        }

        [CommandMethod("TestCommand")]
        public void MyCommand()
        {
            MessageBox.Show("HABR!!!");
        }
    }
}





namespace SolidCreation

{

    public class Commands

    {

        [CommandMethod("SAP")]

        public void SweepAlongPath()

        {

            Document doc =

            Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument;

            Database db = doc.Database;

            Editor ed = doc.Editor;



            // Ask the user to select a region to extrude



            PromptEntityOptions peo1 = new PromptEntityOptions("\nSelect profile or curve to sweep: ");



            peo1.SetRejectMessage("\nEntity must be a region, curve or planar surface.");

            peo1.AddAllowedClass( typeof(Region), false);

            peo1.AddAllowedClass(typeof(Curve), false);

            peo1.AddAllowedClass(typeof(PlaneSurface), false);



            PromptEntityResult per = ed.GetEntity(peo1);



            if (per.Status != PromptStatus.OK)

                return;



            ObjectId regId = per.ObjectId;



            // Ask the user to select an extrusion path



            PromptEntityOptions peo2 = new PromptEntityOptions("\nSelect path along which to sweep: ");



            peo2.SetRejectMessage("\nEntity must be a curve.");

            peo2.AddAllowedClass(typeof(Curve), false);



            per = ed.GetEntity(peo2);



            if (per.Status != PromptStatus.OK)

                return;



            ObjectId splId = per.ObjectId;



            PromptKeywordOptions pko = new PromptKeywordOptions("\nSweep a solid or a surface?");

            pko.AllowNone = true;

            pko.Keywords.Add("SOlid");

            pko.Keywords.Add("SUrface");

            pko.Keywords.Default = "SOlid";



            PromptResult pkr = ed.GetKeywords(pko);



            bool createSolid = (pkr.StringResult == "SOlid");



            if (pkr.Status != PromptStatus.OK)

                return;



            // Now let's create our swept surface



            Transaction tr = db.TransactionManager.StartTransaction();

            using (tr)

            {

                try

                {

                    Entity sweepEnt =

                    tr.GetObject(regId, OpenMode.ForRead) as Entity;



                    Curve pathEnt =

                    tr.GetObject(splId, OpenMode.ForRead) as Curve;



                    if (sweepEnt == null || pathEnt == null)

                    {

                        ed.WriteMessage(

                        "\nProblem opening the selected entities."

                        );

                        return;

                    }



                    // We use a builder object to create

                    // our SweepOptions



                    SweepOptionsBuilder sob = new SweepOptionsBuilder();



                    // Align the entity to sweep to the path



                    sob.Align = SweepOptionsAlignOption.AlignSweepEntityToPath;



                    // The base point is the start of the path



                    sob.BasePoint = pathEnt.StartPoint;
                    // The profile will rotate to follow the path



                    sob.Bank = true;



                    // Now generate the solid or surface...



                    Entity ent;



                    if (createSolid)

                    {

                        Solid3d sol = new Solid3d();



                        sol.CreateSweptSolid(

                        sweepEnt,

                        pathEnt,

                        sob.ToSweepOptions()

                        );



                        ent = sol;

                    }

                    else

                    {

                        SweptSurface ss = new SweptSurface();



                        ss.CreateSweptSurface(

                        sweepEnt,

                        pathEnt,

                        sob.ToSweepOptions()

                        );



                        ent = ss;

                    }



                    // ... and add it to the modelspace



                    BlockTable bt = (BlockTable)tr.GetObject(db.BlockTableId, OpenMode.ForRead);



                    BlockTableRecord ms = (BlockTableRecord)tr.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite);

                    ms.AppendEntity(ent);

                    tr.AddNewlyCreatedDBObject(ent, true);



                    tr.Commit();

                }

                catch

                { }

            }

        }

    }

}