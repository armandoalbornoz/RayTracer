Instructions to run the program:

First way:
The first and easiest way to run this program is to have visual studio. After having donwloaded the zip file and extracted the content
you will have a RayTracer-master folder. Enter into this folder, double click on RayTracer.sln. This will open  visual studio. Change x64
to x86. Run the program using the green button.

Second way MSBUILD:
First, if you do not have MSBUILD, you need to install it. You can find it here https://dotnet.microsoft.com/en-us/download/dotnet/8.0. 
After you install it, add the directory of the msbuild.exe install on your machine to the PATH environment 
variable. Now, After having donwloaded the zip file and extracted the content
you will have a RayTracer-master folder. Enter into this folder, then enter into the folder RayTracer. In this folder open open the terminal
(in my case gitbash) and run the command "msbuild.exe RayTracer.vcxproj -p:Platform=x86". The .exe file can be found in the Debug folder. 

To Test the program you can go to the main function and modify the scene. The scene consists fo the following code:

    Scene scene(std::make_shared<Sphere>(Vector3d(-40, 0, 0), 20, Vector3d(0.3,0.2, 0.4), Vector3d(1,1,1), Vector3d(0.3, 0.2, 0.4), Vector3d(0,0,0)));
    scene.add(std::make_shared<Sphere>(Vector3d(35, 0, 20), 20, Vector3d(0.3, 0.8,0.6), Vector3d(0,0,0), Vector3d(0.3, 0.8, 0.6), Vector3d(0, 0, 0)));
    scene.add(std::make_shared<Triangle>(Vector3d(-20, -20, 0), Vector3d(0 , -20, -20), Vector3d(0,20,-10), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0), Vector3d(0, 0.4, 0.4), Vector3d(0,0,0)));
    scene.add(std::make_shared<Triangle>(Vector3d(20, -20, 0), Vector3d(0, -20, -20), Vector3d(0, 20, -10), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0)));
    scene.add(std::make_shared<Triangle>(Vector3d(-20, -20, 0), Vector3d(20, -20, 0), Vector3d(0, 20, -10), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0)));
    scene.add(std::make_shared<Triangle>(Vector3d(-20, -20, 0), Vector3d(20, -20, 0), Vector3d(0, -20, -20), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0)));

    OrthographicCamera ortographicCamera(Vector3d(20, 50, -125), Vector3d(-20, -50, 125), Vector3d(200, 0, 0), width, height);
    PerspectiveCamera perspectiveCamera(Vector3d(20, 50, -125), Vector3d(-20, -50, 125), Vector3d(200, 0, 0), width, height, 100);
    LightSource light(Vector3d(1,1,1), Vector3d(-150, 300, 50), Vector3d(1.2,1.2,1.2));

So if you wanto to change the center of the ortographic camera to be (-50, 50, -125), you would write

    OrthographicCamera ortographicCamera(Vector3d(-50, 50, -125), Vector3d(-20, -50, 125), Vector3d(200, 0, 0), width, height);

  In order to see what each of the vectors passed to the constructors of the surfaces and cameras do, simply check the respective class files. In the above example the first vector of the constructor 
  of the ortographicCamera was the center of the camera.

Similarly, for the shading you simply modify the vectors passed to the constructors. (Check the classes to see which vectors are the ones that modidy the shading).
