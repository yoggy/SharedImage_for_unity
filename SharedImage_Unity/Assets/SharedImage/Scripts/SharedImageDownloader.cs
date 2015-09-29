using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;

public class SharedImageDownloader : MonoBehaviour {

    string name_ = "testname";
    public string Name
    {
        get { return name_; }
        set
        {
            if (value != null && value.Length > 0)
            {
                name_ = value;
            }
        }
    }

    int width_ = 640;
    public int Width {
        get {
            return width_;
        }
        set
        {
            if (value > 0)
            {
                width_ = value;
            }
        }
    }
    int height_ = 480;
    public int Height
    {
        get
        {
            return height_;
        }
        set
        {
            if (value > 0)
            {
                height_ = value;
            }
        }
    }

    Texture2D shared_texture_;
    public Texture sharedTexture
    {
        get { return shared_texture_; }
        set { }
    }

    System.IntPtr handle_;
    Color32 [] pixels_;
    private GCHandle pixels_handle_;
    private IntPtr pixels_ptr_;

    void Start()
    {
        handle_ = SharedImageDLLAPI.SharedImageCreate(name_, width_, height_);
        shared_texture_ = new Texture2D(width_, height_, TextureFormat.RGB24, false);
        pixels_ = shared_texture_.GetPixels32();
        pixels_handle_ = GCHandle.Alloc(pixels_, GCHandleType.Pinned);
        pixels_ptr_ = pixels_handle_.AddrOfPinnedObject();
    }

    void Update()
    {
        SharedImageDLLAPI.SharedImageDownload(handle_, pixels_ptr_);
        shared_texture_.SetPixels32(pixels_);
        shared_texture_.Apply();
    }

    void OnApplicationQuit()
    {
        if (handle_ != null)
        {
            SharedImageDLLAPI.SharedImageRelease(handle_);
            handle_ = IntPtr.Zero;
        }
    }

}
