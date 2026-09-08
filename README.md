# JifInjector

a simple open source C++ mono injector 

<img width="571" height="338" alt="Photo" src="https://github.com/user-attachments/assets/0e830095-e753-4732-8cc4-b812d6b764ce" />

# usage
- select a dll from files
- select a program
- enter the namespace, class and method
- click inject


# example
example of a simple static method that can be used as the load entry point:


```Csharp
namespace Loading
{
    public class Loader
    {
        public static void Load()
        {
            // Initialize components
            
            Console.WriteLine("Loaded");
        }
    }
}
```

