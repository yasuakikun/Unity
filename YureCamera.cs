using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class YureCamera : MonoBehaviour
{
    [SerializeField] GameObject[] shakeObjects;
    [SerializeField] float ShakeTime;
    [SerializeField] float ShakeDur;
    private CharacterController cCon;
    private void Start()
    {
        cCon = GetComponent<CharacterController>();
    }

    public void OnTriggerStay(Collider xhit)
    {
        switch (xhit.gameObject.tag)
        {
            case "EnemyHit":
                Shake(shakeObjects);

                break;
            case "WolfHit":
                Shake(shakeObjects);
                break;
            case "HobgoHit":
                Shake(shakeObjects);
                break;
            case "goblinHit":
                Shake(shakeObjects);
                break;
            case "TrollHit":
                Shake(shakeObjects);
                break;
        }
    }

    public void Shake(GameObject[] shakeObjects)
    {
        foreach(var shakeObject in shakeObjects)
        {
            iTween.ShakePosition(shakeObject, Vector3.one * ShakeTime, ShakeDur);

            iTween.PunchPosition(shakeObject, iTween.Hash("x", 0.2f, "y", 0.1f, "time", 0.1f));
        }
    }
}