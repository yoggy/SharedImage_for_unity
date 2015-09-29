using UnityEngine;
using System.Collections;

public class SampleScript : MonoBehaviour {

    Material material;
    SharedImageDownloader shared_image;

	void Start () {
        material = gameObject.GetComponent<Renderer>().material;
        shared_image = gameObject.GetComponent<SharedImageDownloader>();
	}
	
	void Update () {
        material.mainTexture = shared_image.sharedTexture;
    }
}
