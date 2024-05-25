#include "HashTable.h"
using namespace std;

int main()
{
    HashTable x;
    x.InsertNode("anemia", "A condition in which there is a deficiency of red cells or of hemoglobin in the blood.");
    x.InsertNode("bronchitis", "Inflammation of the mucous membrane in the bronchial tubes.");
    x.InsertNode("diabetes", "A group of diseases that result in too much sugar in the blood.");
    x.InsertNode("hypertension", "A condition in which the force of the blood against the artery walls is too high.");
    x.InsertNode("asthma", "A condition in which a person's airways become inflamed, narrow and swell, and produce extra mucus.");
    x.InsertNode("hepatitis", "Inflammation of the liver, usually caused by a viral infection.");
    x.InsertNode("stroke", "A condition where poor blood flow to the brain results in cell death.");
    x.InsertNode("osteoarthritis", "A type of arthritis that occurs when flexible tissue at the ends of bones wears down.");
    x.InsertNode("pneumonia", "Infection that inflames air sacs in one or both lungs, which may fill with fluid.");
    x.InsertNode("migraine", "A headache of varying intensity, often accompanied by nausea and sensitivity to light and sound.");
    x.InsertNode("allergy", "A condition in which the immune system reacts abnormally to a foreign substance.");
    x.InsertNode("pancreatitis", "Inflammation of the pancreas.");
    x.InsertNode("osteoporosis", "A condition in which bones become weak and brittle.");
    x.InsertNode("scoliosis", "A sideways curvature of the spine.");
    x.InsertNode("depression", "A mood disorder that causes a persistent feeling of sadness and loss of interest.");
    x.InsertNode("epilepsy", "A disorder in which nerve cell activity in the brain is disturbed, causing seizures.");
    x.InsertNode("glaucoma", "A group of eye conditions that can cause blindness.");
    x.InsertNode("cystitis", "Inflammation of the bladder.");
    x.InsertNode("rheumatoid arthritis", "A chronic inflammatory disorder affecting many joints, including those in the hands and feet.");
    x.InsertNode("hypothyroidism", "A condition in which the thyroid gland doesn't produce enough hormones.");
    x.InsertNode("hyperthyroidism", "The overproduction of a hormone by the butterfly-shaped gland in the neck (thyroid).");
    x.PrintTable();
    cout << endl;
    x.RemoveNode("diabetes");
    cout << endl << x.GetSize();
    x.PrintTable();

    cout << endl << x.SearchTable("anemia");
    cout << endl << x.GetSize();

    return 0;
}

