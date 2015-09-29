using UnityEngine;
using System.Collections;

public class SharedImageDLLAPI : MonoBehaviour {
    [System.Runtime.InteropServices.DllImport("SharedImage_UnityDLL")]
    public static extern System.IntPtr SharedImageCreate(string name, int width, int height);

    [System.Runtime.InteropServices.DllImport("SharedImage_UnityDLL")]
    public static extern System.IntPtr SharedImageGetBuffer(System.IntPtr handle);

    [System.Runtime.InteropServices.DllImport("SharedImage_UnityDLL")]
    public static extern void SharedImageRelease(System.IntPtr handle);

    [System.Runtime.InteropServices.DllImport("SharedImage_UnityDLL")]
    public static extern void SharedImageDownload(System.IntPtr handle, System.IntPtr buf);

    [System.Runtime.InteropServices.DllImport("SharedImage_UnityDLL")]
    public static extern void SharedImageUpload(System.IntPtr handle, System.IntPtr buf);
}
