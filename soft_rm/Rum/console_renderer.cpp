#include "Proxy.hpp"
#include <QtGui/QMainWindow>

/// params: rum.exe code.sdf width height output_file
int ConsoleMode(int argc, char* argv[])
{
    Proxy proxy;

    if (argc != 5) {
        std::cout << "Wrong params, example:\n" <<
            "rum.exe scene.sdf width height output_file\n\n";
        return 2;
    }


    QString width(argv[2]), height(argv[3]);
    QString output_file(argv[4]);
    QString file(argv[1]);

    QFile qfile(file);

    if (!qfile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(NULL, QObject::tr("Sphere Marcher"), QObject::tr("Cannot read file %1:\n %2").arg(file).arg(qfile.errorString()));
        return 1;
    }
    else
    {
        QTextStream content(&qfile);
        QString code = content.readAll();
        qfile.close();

        std::cout << "Compiling..." ;
        bool compilation = proxy.Compile(code);

        std::cout << (compilation? "OK" : "FAILED") << '\n';

        if (compilation == false)
            return 8;

        proxy.SetMaxSteps(128);
        
        uint w, h;
        w = width.toUInt();
        h = height.toUInt();

        QImage output = proxy.Render(w, h);
        
        output.save(output_file);
    }

    return 0;
}