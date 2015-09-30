using UnityEngine;
using System.Collections;

public class SampleScript : MonoBehaviour {

    Material material;
    SharedImageDownloader shared_image;

	void Start () {
        // setup shared image texture
        material = gameObject.GetComponent<Renderer>().material;
        shared_image = gameObject.GetComponent<SharedImageDownloader>();
        material.mainTexture = shared_image.sharedTexture;
    }
}
